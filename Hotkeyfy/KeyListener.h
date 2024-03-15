#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <Windows.h>

#pragma comment(lib, "User32.lib")

class KeyListener
{
public:
	static void init();

	static void cleanup();

	static void listen();

	static const std::vector<std::wstring> getKeys();

	static bool isListening();

	static void enableHotkeys();
	static void disableHotkeys();

	static std::wstring getKeyName(DWORD _scanCode);

	static std::vector<DWORD> PlayPauseKeys;
private:
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

	static void loop(std::stop_token _stoken);

	static std::vector<std::wstring> keyList;
	static std::mutex keyList_mutex;

	static std::jthread loopTh;

	static HHOOK keyboardHook;

	static bool doListen;

	static bool hotkeysEnabled;
};

