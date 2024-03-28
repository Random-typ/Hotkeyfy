#pragma once
#ifndef __HotkeyfyConfig_H__
#define __HotkeyfyConfig_H__

#include <vector>
#include <filesystem>
#include <string>
#include <map>
#include <fstream>
#include <Windows.h>
#include "HotkeyfyExport.h"


class HOTKEYFYAPI_DECLSPEC config
{
public:
	static std::pair<std::vector<DWORD>, bool/*consume*/> getHotkeys(const std::string& _action);

	static void setHotkeys(const std::string& _action, const std::vector<DWORD>& _keys, bool _consume);

	static void setVolumeIncrement(double _value);
	static void setVolumeDecrement(double _value);

	static double getVolumeIncrement();
	static double getVolumeDecrement();

	// @returns true if successful, false otherwise
	static void load(const std::wstring& _path);
	static void reload();

	// @returns true if successful, false otherwise
	static void save();

	static void setAutoStart(bool _autoStart);
	static bool getAutoStart();

	static void setProcess(const std::string& _process);
	static std::string getProcess();

	static const std::string launchedFromService;

	static std::map<std::string/*action*/, std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/>>& getHotkeys();
private:
	static double volumeIncrement;
	static double volumeDecrement;
	static std::string process;

	static std::map<std::string/*action*/, std::pair<std::vector<DWORD>/*keys*/, bool/*consume*/>> hotkeys;
	static std::wstring path;
};
#endif // !__HotkeyfyConfig_H__
