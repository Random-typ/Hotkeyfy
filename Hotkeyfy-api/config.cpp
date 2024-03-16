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

void config::setHotkeys(const std::wstring& _action, const std::vector<DWORD>& _keys)
{
    hotkeys[_action].first = _keys;
}

void config::load(const std::wstring& _path)
{
    hotkeys.clear();
    path = _path;
    std::filesystem::create_directories(std::filesystem::path(path).root_path());
    std::ifstream fs(path);
    if (fs.is_open())
    {
        return;
    }
    json conf = json::parse(fs);
    autoStart = conf["autostart"];
    for (auto& action : conf["actions"])
    {
        std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/> data;
        data.second = action["consume"];
        for (auto& key : action["keys"])
        {
            data.first.emplace_back(key);
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
            {"consume", key.second.second},
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
