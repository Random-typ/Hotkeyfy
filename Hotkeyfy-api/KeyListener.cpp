#include "KeyListener.h"
#include <iostream>

Keys KeyListener::keyList;
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

const Keys& KeyListener::getKeys()
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

std::wstring KeyListener::getKeyName(KeystrokeMessage _extendedKeyCode)
{
	std::wstring key;
	int len = 256;
	key.resize(len);
	
	if (len = GetKeyNameTextW(_extendedKeyCode.scanCode << 16, key.data(), key.size()); !len) {
		return std::wstring();
	}
	key.resize(len);
	return key + (_extendedKeyCode.flags ? L"(special)" : L"");
}

void KeyListener::doAction(std::string_view _action)
{
	// time between actions must be 100 ms or more unless the action controls volume
	static std::chrono::milliseconds lastDoActionCall = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	if (_action != "Volume Up" && 
		_action != "Volume Down" && 
		(std::chrono::system_clock::now().time_since_epoch() - lastDoActionCall).count() < 100)
	{
		return;
	}
	lastDoActionCall = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

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

	// convert the message to "useful" value

	KeystrokeMessage keyCode{ 0 };
	keyCode.scanCode = ((KBDLLHOOKSTRUCT*)lParam)->scanCode;
	keyCode.flags = ((KBDLLHOOKSTRUCT*)lParam)->flags & LLKHF_EXTENDED;
	
	KBDLLHOOKSTRUCT*  pppp = ((KBDLLHOOKSTRUCT*)lParam);
	
	bool extendedKey = ((lParam >> 24) & 0x01);

	bool numpadKey = (keyCode.scanCode >= 0x47 && keyCode.scanCode <= 0x53) || // Numpad keys
		(keyCode.scanCode == 0x35 && !extendedKey);       // "/" on numpad

	if (numpadKey) {
		//keyCode.scanCode |= 0x100; // Set the extended bit
	}

	if (!keyCode.scanCode)
	{
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}

 	if (doListen)
	{
		if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			doListen = false;
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}

		std::wstring key = getKeyName(keyCode);
		if (key.empty())
		{
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}
		keyList_mutex.lock();
		if (!std::any_of(keyList.begin(), keyList.end(), [keyCode](KeystrokeMessage key){
			return keyCode == key;
			}))
		{
			keyList.emplace_back(keyCode);
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
		DWORD dd = MapVirtualKeyA(VK_RMENU, MAPVK_VK_TO_VSC_EX);
		

		if (!i.second.first.empty() && std::all_of(i.second.first.begin(), i.second.first.end(), [keyCode](KeystrokeMessage key) {
			DWORD ee = GetAsyncKeyState(VK_RMENU);
			std::cout << ee << "\n";
			bool keyState = false;
			DWORD extendedScanCode = key.scanCode | (key.flags ? (0xe0 << 8) : 0);
			if (extendedScanCode == MapVirtualKeyA(VK_RMENU, MAPVK_VK_TO_VSC_EX))// right alt is special :^)
			{
				
				keyState = true;
			}
			else
			{
				keyState = 1;
			}

			return (keyCode.scanCode == key.scanCode) || (GetKeyState(MapVirtualKeyA(extendedScanCode, MAPVK_VSC_TO_VK_EX)) & 0x8000);
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
