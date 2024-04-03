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

// https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input#keystroke-message-flags
struct KeystrokeMessage {
	KeystrokeMessage(uint64_t _value) : scanCode(_value & 0xFFFFFFFF), flags(_value >> 32), unused(0){}
	DWORD scanCode;
	DWORD flags : 1;
	DWORD unused : 31;

	uint64_t toNum() const
	{
		return uint64_t(scanCode) | (uint64_t(flags) << 32);
	}

	bool operator==(KeystrokeMessage _other) const {
		return _other.toNum() == toNum();
	}
};

class Keys : public std::vector<KeystrokeMessage> {
public:
	std::vector<uint64_t> toNumbers() const {
		std::vector<uint64_t> nums;
		for (auto& i : *this)
		{
			nums.emplace_back(i.toNum());
		}
		return nums;
	}
};

using Action = std::pair<Keys, bool/*consume*/>;
using ActionMap = std::map<std::string/*action name*/, Action>;

class HOTKEYFYAPI_DECLSPEC config
{
public:
	static Action getHotkeys(const std::string& _action);

	static void setHotkeys(const std::string& _action, const Keys& _keys, bool _consume);

	// Check wether specified hotkeys are already used by an action that is not the specified action
	// @returns if a value is returned the name of the action, which has the keys specified
	static std::optional<std::string> alreadySet(const std::string& _actionName, const Keys& _keys);

	static void setVolumeIncrement(double _value);
	static void setVolumeDecrement(double _value);

	static double getVolumeIncrement();
	static double getVolumeDecrement();

	static void load(const std::wstring& _path);
	static void reload();

	static void save();

	static void setAutoStart(bool _autoStart);
	static bool getAutoStart();

	static void setProcess(const std::string& _process);
	static std::string getProcess();

	static const std::string launchedFromService;
	static const std::string showGUI;

	static ActionMap& getHotkeys();
private:
	static double volumeIncrement;
	static double volumeDecrement;
	static std::string process;

	static ActionMap hotkeys;
	static std::wstring path;
};
#endif // !__HotkeyfyConfig_H__
