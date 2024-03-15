#include "pch.h"
#include "config.h"

std::map<std::wstring, std::pair<std::vector<DWORD>, config_metadata>> config::hotkeys;
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
    // i wanted to do this with json. But i was bored. so its binary now
    // structure: (repeats)
    // null terminated wide string (action name)
    // uint64_t (number of elements in array)
    // array of DWORD (each DWORD is one key)
    std::filesystem::create_directories(std::filesystem::path(path).root_path());
    std::ifstream fs(path);
    if (fs.is_open())
    {
        return;
    }
    std::string data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    fs.close();
    size_t off = 0;
    while (off < data.size())
    {
        off = wcsnlen_s((wchar_t*)&data[off], data.size() - off);
        std::wstring name((wchar_t*)&data[off], off);
        off++;
        if (off + sizeof(config_metadata) > data.size())
        {
            return;
        }

        config_metadata keyCount = *(config_metadata*)&data[off];
        if (keyCount.count * sizeof(DWORD) > data.size())
        {
            return;
        }

        std::vector<DWORD> keys;
        keys.resize(keyCount.count);

        memcpy_s(keys.data(), keys.size(), &data[off], data.size() - off);

        off += keyCount.count * sizeof(DWORD);

        hotkeys[name].first = keys;
    }
}

void config::save()
{
    size_t size = 0;
    for (auto& hotkey : hotkeys)
    {
        size += (hotkey.first.size() + 1) * sizeof(wchar_t);
        size += sizeof(config_metadata);
        size += hotkey.second.first.size() * sizeof(DWORD);
    }
    std::vector<char> data;
    data.resize(size);
    size_t off = 0;
    for (auto& hotkey : hotkeys)
    {
        memcpy_s(&data[off], data.size() - off, hotkey.first.data(), (hotkey.first.size() + 1) * sizeof(wchar_t));
        off += (hotkey.first.size() + 1) * sizeof(wchar_t);

        config_metadata meta = hotkey.second.second;
        meta.count = hotkey.second.first.size();
        memcpy_s(&data[off], data.size() - off, &meta, sizeof(config_metadata));

        off += sizeof(config_metadata);

        memcpy_s(&data[off], data.size() - off, hotkey.second.first.data(), arraySize * sizeof(DWORD));

        off += arraySize * sizeof(DWORD);
    }
    std::ofstream of(path);
    if (!of.is_open())
    {
        return;
    }
    of.write(data.data(), data.size());
    of.close();
}
