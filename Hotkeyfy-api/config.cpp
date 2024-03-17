#include "config.h"
#include "nlohmann_json.hpp"

using json = nlohmann::json;

bool config::autoStart = true;

std::map<std::wstring/*action*/, std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/>> config::hotkeys;
std::wstring config::path;

std::vector<DWORD> config::getHotkeys(const std::wstring& _action)
{
    auto iterator = hotkeys.find(_action);
    if (iterator == hotkeys.end())
    {
        return std::vector<DWORD>();
    }
    return iterator->second.first;
}

void config::setHotkeys(const std::wstring& _action, const std::vector<DWORD>& _keys, bool _consume)
{
    hotkeys[_action].first = _keys;
    hotkeys[_action].second = _consume;
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
        json conf = json::parse(fs);
    }
    catch (const json::exception&)
    {
        return;
    }
    if (!conf.contains("actions") || !conf.contains("autostart"))
    {
        return;
    }
    autoStart = conf["autostart"];
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
        {"autostart", autoStart},
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
