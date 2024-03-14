#include "pch.h"
#include "KeyListener.h"

std::vector<std::wstring> KeyListener::keyList;
std::mutex KeyListener::keyList_mutex;

std::jthread KeyListener::loopTh;

HHOOK KeyListener::keyboardHook = NULL;

bool KeyListener::doListen = false;

bool KeyListener::hotkeysEnabled = false;


void KeyListener::init()
{
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
	loopTh = std::jthread(loop);
}

void KeyListener::cleanup()
{
	loopTh.request_stop();
	PostThreadMessageA(GetThreadId(loopTh.native_handle()), WM_USER, 0, 0);
	loopTh.join();
	UnhookWindowsHookEx(keyboardHook);
}

void KeyListener::listen()
{
	doListen = true;
}

const std::vector<std::wstring> KeyListener::getKeys()
{
	return keyList;
}

bool KeyListener::isListening()
{
	return doListen;
}

void KeyListener::enableHotkeys()
{
	hotkeysEnabled = true;
}

void KeyListener::disableHotkeys()
{
	hotkeysEnabled = false;
}

LRESULT KeyListener::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* kbStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

	if (doListen)
	{
		if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			doListen = false;
		}
		std::wstring key;
		key.resize(256);
		if (!GetKeyNameTextW(lParam, key.data(), key.size()))
		{
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}
		keyList_mutex.lock();
		keyList.emplace_back(key);
		keyList_mutex.unlock();
	}
	if (!hotkeysEnabled)
	{
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}

	


	return LRESULT();
}

void KeyListener::loop(std::stop_token _stoken)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) && !_stoken.stop_requested()) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
