#include "pch.h"
#include "KeyListener.h"

std::vector<DWORD> KeyListener::keyList;
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
	if (keyboardHook)
	{
		UnhookWindowsHookEx(keyboardHook);
		keyboardHook = NULL;
	}
}

void KeyListener::listen()
{
	keyList_mutex.lock();
	keyList.clear();
	keyList_mutex.unlock();
	doListen = true;
}

const std::vector<DWORD> KeyListener::getKeys()
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

std::wstring KeyListener::getKeyName(DWORD _scanCode)
{
	std::wstring key;
	key.resize(64);
	int len;
	if (len = GetKeyNameTextW(_scanCode << 16, key.data(), key.size()); !len)
	{
		return std::wstring();
	}
	key.resize(len);
	return key;
}

LRESULT KeyListener::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* kbStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

	if (doListen)
	{
		if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			doListen = false;
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}

		std::wstring key = getKeyName(kbStruct->scanCode);
		if (key.empty())
		{
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}
		keyList_mutex.lock();
		if (std::none_of(keyList.begin(), keyList.end(), [&](DWORD key){
			return kbStruct->scanCode == key;
			}))
		{
			keyList.emplace_back(kbStruct->scanCode);
		}
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
	UnhookWindowsHookEx(keyboardHook);
	keyboardHook = NULL;
}
