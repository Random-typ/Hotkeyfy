#include "config.h"
#include "nlohmann_json.hpp"

using json = nlohmann::json;

const std::string config::launchedFromService = "LaunchedFromService";

double config::volumeIncrement = 1.0;
double config::volumeDecrement = 1.0;
std::string config::process = "spotify.exe";

std::map<std::string/*action*/, std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/>> config::hotkeys;
std::wstring config::path;

std::pair<std::vector<DWORD>, bool/*consume*/> config::getHotkeys(const std::string& _action)
{
    auto iterator = hotkeys.find(_action);
    if (iterator == hotkeys.end())
    {
        return { std::vector<DWORD>(), false };
    }
    return iterator->second;
}

void config::setHotkeys(const std::string& _action, const std::vector<DWORD>& _keys, bool _consume)
{
    if (_keys.size())
    {
        hotkeys[_action].first = _keys;
    }
    hotkeys[_action].second = _consume;
}

void config::setVolumeIncrement(double _value)
{
    volumeIncrement = _value;
}

void config::setVolumeDecrement(double _value)
{
    volumeDecrement = _value;
}

double config::getVolumeIncrement()
{
    return volumeIncrement;
}

double config::getVolumeDecrement()
{
    return volumeDecrement;
}

void config::load(const std::wstring& _path)
{
    hotkeys.clear();
    path = _path;
    std::filesystem::create_directories(std::filesystem::path(path).parent_path());
    std::ifstream fs(path);
    if (!fs.is_open())
    {
        return;
    }
    json conf;
    try
    {
        conf = json::parse(fs);
    }
    catch (const json::exception&)
    {
        return;
    }

    if (!conf.contains("actions"))
    {
        return;
    }
    
    conf.contains("volumeIncrement") ? volumeIncrement = conf["volumeIncrement"] : 0;
    conf.contains("volumeDecrement") ? volumeDecrement = conf["volumeDecrement"] : 0;
    conf.contains("process") ? process = conf["process"] : 0;

    for (auto& action : conf["actions"])
    {
        std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/> data;
        data.second = action["consume"];
        for (auto& key : action["keys"])
        {
            data.first.emplace_back(key);
        }
        if (!action.contains("action"))
        {
            return;
        }
        hotkeys[action["action"]] = data;
    }
}

void config::save()
{
    json conf = {
        {"volumeIncrement", volumeIncrement},
        {"volumeDecrement", volumeDecrement},
        {"process", process},
        {"actions", {}}
    };


    for (auto& key : hotkeys)
    {
        conf["actions"] += {
            { "action", std::string(key.first.begin(), key.first.end()) },
            { "consume", key.second.second },
            { "keys", key.second.first }
        };
    }
    
    std::ofstream of(path);
    if (!of.is_open())
    {
        return;
    }

    of << conf;
    of.close();
}

void config::setAutoStart(bool _autoStart) {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE | KEY_READ, &key)
        != ERROR_SUCCESS)
    {// failed
        return;
    }

    DWORD size = MAX_PATH;
    std::wstring path;
    path.resize(MAX_PATH);
    if (!QueryFullProcessImageNameW(GetCurrentProcess(), 0, path.data(), &size))
    {// failed
        RegCloseKey(key);
        return;
    }
    path.resize(size);

    std::wstring GUIPath = std::filesystem::path(path).parent_path().wstring() + L"/Hotkeyfy-service.exe";

    if (_autoStart)
    {
        if (RegSetValueExW(key, L"Hotkeyfy", 0, REG_SZ, (BYTE*)GUIPath.c_str(), (GUIPath.size() * sizeof(GUIPath[0])) + sizeof(GUIPath[0]))
            != ERROR_SUCCESS)
        {// failed
            RegCloseKey(key);
            return;
        }
    }
    else {
        if (RegDeleteValueW(key, L"Hotkeyfy") != ERROR_SUCCESS)
        {// failed
            RegCloseKey(key);
            return;
        }
    }

    RegCloseKey(key);
}

bool config::getAutoStart() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE | KEY_READ, &key)
        != ERROR_SUCCESS)
    {// failed
        return false;
    }

    bool autoStart = RegGetValueW(key, NULL, L"Hotkeyfy", RRF_RT_REG_SZ, NULL, NULL, NULL) != ERROR_FILE_NOT_FOUND;

    RegCloseKey(key);
    return autoStart;
}

void config::setProcess(const std::string& _process)
{
    process = _process;
}

std::string config::getProcess()
{
    return process;
}