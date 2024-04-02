#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <Windows.h>
#include "HotkeyfyExport.h"
#include "config.h"
#include "ProcessAudioControl.h"

#pragma comment(lib, "User32.lib")

// For some reason GetKeyNameTextW(), MapVirtualKeyA() and KeyboardProc() use different formats
// for extended keys. That's why i have this abomination now:
// ExtendedKeyCode:
// for storing as simple DWORDs
// 
// VirtualKey:
// normal virtual key 
//
// ExtendedKeyNameCode:
// extended virtual key specifically for GetKeyNameTextW()

#define ScanCodeToExtendedKeyCode(scanCode, flags) (scanCode << 16 | (flags & 0x1 ? 0xe0 << 8 : 0))
#define ExtendedKeyCodeToVirtualKey(extendedKey) (MapVirtualKeyA(extendedKey >> 16 | (extendedKey & 0xFFFF), MAPVK_VSC_TO_VK_EX))
#define ExtendedKeyCodeToExtendedKeyNameCode(extendedKey) (extendedKey | (extendedKey & 0xFFFF ? (KF_EXTENDED << 16) & 0xFFFF0000 : 0))

class HOTKEYFYAPI_DECLSPEC KeyListener
{
public:
	static void init();

	static void cleanup();

	static void listen();

	static const Keys& getKeys();

	static bool isListening();

	static void enableHotkeys();
	static void disableHotkeys();

	static std::wstring getKeyName(KeystrokeMessage _extendedKeyCode);

	static void doAction(std::string_view _action);

	static void reloadConfig();

	static ProcessAudioControl audioControl;
private:
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

	static void loop(std::stop_token _stoken);

	static Keys keyList;
	static std::mutex keyList_mutex;

	static std::jthread loopTh;

	static HHOOK keyboardHook;

	static bool doListen;

	static std::atomic_bool hotkeysEnabled;
};

