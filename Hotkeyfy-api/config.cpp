#include "config.h"
#include "nlohmann_json.hpp"

using json = nlohmann::json;

const std::string config::launchedFromService = "LaunchedFromService";
const std::string config::showGUI = "-gui";

double config::volumeIncrement = 1.0;
double config::volumeDecrement = 1.0;
std::string config::process = "Spotify.exe";

ActionMap config::hotkeys;
std::wstring config::path;
std::map<KeystrokeMessage, KeystrokeMessageStatus> config::keyStatus;
std::mutex config::keyStatus_mutex;


Action config::getHotkeys(const std::string& _action)
{
    auto iterator = hotkeys.find(_action);
    if (iterator == hotkeys.end())
    {
        return Action();
    }
    return iterator->second;
}

void config::setHotkeys(const std::string& _action, const Keys& _keys, bool _consume)
{
    if (_keys.size())
    {
        hotkeys[_action].keys = _keys;
        reloadKeyStatus();
    }
    hotkeys[_action].consume = _consume;
}

std::optional<std::string> config::alreadySet(const std::string& _actionName, const Keys& _keys)
{
    for (auto& hotkey : hotkeys)
    {
        if (_actionName != hotkey.first &&
            hotkey.second.keys.size() == _keys.size() &&
            std::all_of(hotkey.second.keys.begin(), hotkey.second.keys.end(), [_keys](KeystrokeMessage key) {
                return std::any_of(_keys.begin(), _keys.end(), [key](KeystrokeMessage newkey) {
                    return newkey == key;
                    });
                }))
        {
            return hotkey.first;
        }
    }
    return {};
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
    path = _path;
    reload();
}

void config::reload()
{
    hotkeys.clear();
    keyStatus_mutex.lock();
    keyStatus.clear();
    keyStatus_mutex.unlock();

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
        Action data;
        data.consume = action["consume"];
        for (auto& key : action["keys"])
        {
            data.keys.emplace_back(key);
        }
        if (!action.contains("action"))
        {
            return;
        }
        hotkeys[action["action"]] = data;
    }
    reloadKeyStatus();
}

void config::reloadKeyStatus()
{
    keyStatus_mutex.lock();
    keyStatus.clear();
    for (auto& i : hotkeys)
    {
        for (auto& j : i.second.keys)
        {
            keyStatus.emplace(j, KeystrokeMessageStatus::unknown);
        }
    }
    keyStatus_mutex.unlock();
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
            { "action", key.first },
            { "consume", key.second.consume },
            { "keys", key.second.keys.toNumbers() }
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

void config::resetKeyStatus()
{
    for (auto& hotkey : keyStatus)
    {
        hotkey.second = KeystrokeMessageStatus::unknown;
    }
}

bool config::isKeyDown(KeystrokeMessage _key)
{
    auto status = keyStatus.find(_key);
    if (status == keyStatus.end())
    {
        return false;
    }
    return status->second == KeystrokeMessageStatus::pressed;
}

void config::updateKeyStatus(KeystrokeMessage _key, WPARAM _status)
{
    auto key = keyStatus.find(_key);
    if (key == keyStatus.end())
    {
        return;
    }
    keyStatus_mutex.lock();
    switch (_status)
    {
    case WM_KEYUP:
    case WM_SYSKEYUP:
        key->second = KeystrokeMessageStatus::notPressed;
        break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        key->second = KeystrokeMessageStatus::pressed;
        break;
    }
    keyStatus_mutex.unlock();
}

bool config::hasKey(KeystrokeMessage _key) 
{
    return keyStatus.contains(_key);
}


ActionMap& config::getHotkeys()
{
    return hotkeys;
}
