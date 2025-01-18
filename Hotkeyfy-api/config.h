#pragma once
#ifndef __HotkeyfyConfig_H__
#define __HotkeyfyConfig_H__

#include <vector>
#include <filesystem>
#include <string>
#include <map>
#include <mutex>
#include <fstream>
#include <Windows.h>
#include "HotkeyfyExport.h"

// https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input#keystroke-message-flags

struct KeystrokeMessage {
	KeystrokeMessage(uint64_t _value) : scanCode(_value & 0xFFFFFFFF), flags(_value >> 32), unused(0) {}
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
	bool operator<(KeystrokeMessage _other) const {
		return _other.toNum() < toNum();
	}
	bool operator>(KeystrokeMessage _other) const {
		return _other.toNum() > toNum();
	}
};

enum class KeystrokeMessageStatus
{
	unknown,
	pressed,
	// one might say it is depressed
	notPressed
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

struct Action {
	Action() : consume(false) {}
	Keys keys;
	bool consume;
};
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
	static void reloadKeyStatus();

	static void save();

	static void setAutoStart(bool _autoStart);
	static bool getAutoStart();

	static void setProcess(const std::string& _process);
	static std::string getProcess();

	static const std::string launchedFromService;
	static const std::string showGUI;
	static const std::string uninstall;

	static ActionMap& getHotkeys();

	static void resetKeyStatus();

	static bool isKeyDown(KeystrokeMessage _key);

	static void updateKeyStatus(KeystrokeMessage _key, WPARAM _status);

	static bool hasKey(KeystrokeMessage _key);
private:
	static double volumeIncrement;
	static double volumeDecrement;
	static std::string process;

	static ActionMap hotkeys;
	static std::wstring path;

	static std::map<KeystrokeMessage, KeystrokeMessageStatus> keyStatus;
	static std::mutex keyStatus_mutex;
};
#endif // !__HotkeyfyConfig_H__
