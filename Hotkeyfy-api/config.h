#pragma once
#ifndef __HotkeyfyConfig_H__
#define __HotkeyfyConfig_H__

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <Windows.h>

#ifdef HOTKEYFYAPI_EXPORTS
#define CLASS_DECLSPEC    __declspec(dllexport)
#else
#define CLASS_DECLSPEC    __declspec(dllimport)
#endif

class CLASS_DECLSPEC config
{
public:
	static std::vector<DWORD> getHotkeys(const std::wstring& _action);

	static void setHotkeys(const std::wstring& _action, const std::vector<DWORD>& _keys);

	// @returns true if successful, false otherwise
	static void load(const std::wstring& _path);

	// @returns true if successful, false otherwise
	static void save();

	static bool autoStart;
private:
	static std::map<std::wstring/*action*/, std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/>> hotkeys;
	static std::wstring path;
};
#endif // !__HotkeyfyConfig_H__
