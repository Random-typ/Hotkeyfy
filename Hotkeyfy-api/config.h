#pragma once
#ifndef __HotkeyfyConfig_H__
#define __HotkeyfyConfig_H__

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <Windows.h>

#pragma comment(lib, "Advapi32.lib")

#ifdef HOTKEYFYAPI_EXPORTS
#define HOTKEYFYAPI_DECLSPEC    __declspec(dllexport)
#else
#define HOTKEYFYAPI_DECLSPEC    __declspec(dllimport)
#endif

class HOTKEYFYAPI_DECLSPEC config
{
public:
	static std::vector<DWORD> getHotkeys(const std::wstring& _action);

	static void setHotkeys(const std::wstring& _action, const std::vector<DWORD>& _keys, bool _consume);

	static void setVolumeIncrement(double _value);
	static void setVolumeDecrement(double _value);

	// @returns true if successful, false otherwise
	static void load(const std::wstring& _path);

	// @returns true if successful, false otherwise
	static void save();

	static void setAutoStart(bool _autoStart);
	static bool getAutoStart();
private:
	static double volumeIncrement;
	static double volumeDecrement;

	static std::map<std::wstring/*action*/, std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/>> hotkeys;
	static std::wstring path;
};
#endif // !__HotkeyfyConfig_H__
