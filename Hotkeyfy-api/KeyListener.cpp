#include "KeyListener.h"

std::vector<DWORD> KeyListener::keyList;
std::mutex KeyListener::keyList_mutex;

std::jthread KeyListener::loopTh;

HHOOK KeyListener::keyboardHook = NULL;

bool KeyListener::doListen = false;

std::atomic_bool KeyListener::hotkeysEnabled = false;
ProcessAudioControl KeyListener::audioControl;


void KeyListener::init()
{
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
	loopTh = std::jthread(loop);

	reloadConfig();
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

std::wstring KeyListener::getKeyName(DWORD _extendedKeyCode)
{
	std::wstring key;
	key.resize(64);
	int len;
	DWORD code = ExtendedKeyCodeToExtendedKeyNameCode(_extendedKeyCode);
	if (len = GetKeyNameTextW(code, key.data(), key.size()); !len)
	{
		return std::wstring();
	}
	key.resize(len);
	return key;
}

void KeyListener::doAction(std::string_view _action)
{
	if (_action == "Play Pause")
	{
		audioControl.playPause();
		return;
	}
	if (_action == "Previous Track")
	{
		audioControl.prevTrack();
		return;
	}
	if (_action == "Next Track")
	{
		audioControl.nextTrack();
		return;
	}
	if (_action == "Volume Up")
	{
		audioControl.volumeUp(config::getVolumeIncrement() / 100);
		return;
	}
	if (_action == "Volume Down")
	{
		audioControl.volumeDown(config::getVolumeDecrement() / 100);
		return;
	}
}

void KeyListener::reloadConfig() 
{
	std::string exe = config::getProcess();
	audioControl.selectExecutableName(std::wstring(exe.begin(), exe.end()));
}


LRESULT KeyListener::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}
	KBDLLHOOKSTRUCT* kbStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
	// extended scan code
	DWORD scanCode = ScanCodeToExtendedKeyCode(kbStruct->scanCode, kbStruct->flags);

 	if (doListen)
	{
		if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			doListen = false;
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}

		std::wstring key = getKeyName(scanCode);
		if (key.empty())
		{
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}
		keyList_mutex.lock();
		if (std::none_of(keyList.begin(), keyList.end(), [&](DWORD key){
			return kbStruct->scanCode == key;
			}))
		{
			keyList.emplace_back(scanCode);
		}
		keyList_mutex.unlock();
		// listening -> no hotkeys should work
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}
	if (!hotkeysEnabled)
	{
 		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}

  	if (wParam != WM_KEYDOWN && wParam != WM_SYSKEYDOWN)
	{
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}
	auto& hotkeys = config::getHotkeys();

	// hotkey checking
	for (auto& i : hotkeys)
	{
		if (std::all_of(i.second.first.begin(), i.second.first.end(), [scanCode](DWORD key) {
			return scanCode == key || GetAsyncKeyState(ExtendedKeyCodeToVirtualKey(key)) & 0x8000;
			}))
		{
			doAction(i.first);

			if (i.second.second/*consume*/)
			{
				return 1;
			}
			break;
		}
	}

	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
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
