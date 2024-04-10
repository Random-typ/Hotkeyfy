#define NOMINMAX
#include "KeyListener.h"
#include <iostream>

Keys KeyListener::keyList;
std::mutex KeyListener::keyList_mutex;

std::jthread KeyListener::loopTh;

HHOOK KeyListener::keyboardHook = NULL;

bool KeyListener::doListen = false;

std::atomic_bool KeyListener::hotkeysEnabled = false;
ProcessAudioControl KeyListener::audioControl;

/*
// Apparently Microsoft has not finished this library...
#include <GameInput.h>
#include <wrl/client.h>

Microsoft::WRL::ComPtr<IGameInput> gameInput;
Microsoft::WRL::ComPtr<IGameInputDevice> gamepad;
Microsoft::WRL::ComPtr<IGameInputReading> prevReading;

void PollGamepadInput() noexcept
{
	HRESULT hr = GameInputCreate(gameInput.GetAddressOf());

	while (true)
	{
		PollGamepadInput();
	}
	IGameInput* input;

	HRESULT hres = GameInputCreate(&input);

	IGameInputReading* reading;
	while (true)
	{
		hres = input->GetCurrentReading(GameInputKind::GameInputKindKeyboard, nullptr, &reading);

		int keyCount = reading->GetKeyCount();
		std::cout << keyCount << "\n";
		std::vector<GameInputKeyState> state;
		state.resize(keyCount);

		uint32_t u = reading->GetKeyState(keyCount, state.data());

	}

	if (!prevReading)
	{
		if (SUCCEEDED(gameInput->GetCurrentReading(
			GameInputKindGamepad,
			nullptr,
			&prevReading)))
		{
			prevReading->GetDevice(&gamepad);

			// Application-specific code to process the initial reading. 
		}
	}

	else
	{
		Microsoft::WRL::ComPtr<IGameInputReading> nextReading;
		HRESULT hr = gameInput->GetNextReading(
			prevReading.Get(),
			GameInputKindGamepad,
			gamepad.Get(),
			&nextReading);

		if (SUCCEEDED(hr))
		{
			// Application-specific code to process the next reading. 

			prevReading = nextReading;
		}

		else if (hr != GAMEINPUT_E_READING_NOT_FOUND)
		{
			gamepad = nullptr;
			prevReading = nullptr;
		}
	}
}
*/

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
		return std::wstring(L"UnKnOwN");
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
bool altPressed = false;

LRESULT KeyListener::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
#if 0
	auto start = std::chrono::high_resolution_clock::now();
#endif // 0	
	if (nCode < 0 || nCode != HC_ACTION)
	{
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}

	if (wParam != WM_KEYUP && wParam != WM_SYSKEYUP && wParam != WM_KEYDOWN && wParam != WM_SYSKEYDOWN)
	{
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}
	
	// convert the message to "useful" value
	KeystrokeMessage keyCode{ 0 };
	keyCode.scanCode = ((KBDLLHOOKSTRUCT*)lParam)->scanCode;
	keyCode.flags = ((KBDLLHOOKSTRUCT*)lParam)->flags & LLKHF_EXTENDED;
	
	config::updateKeyStatus(keyCode, wParam);

	if (!keyCode.scanCode)
	{
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}

 	if (doListen)
	{
		if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{// key lifted -> stop listening
			doListen = false;
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}

		std::wstring key = getKeyName(keyCode);
		if (key.empty())
		{
			return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
		}
		keyList_mutex.lock();
		if (!std::any_of(keyList.begin(), keyList.end(), [keyCode, lParam](KeystrokeMessage key){
			return keyCode == key;
			}))
		{
			keyList.emplace_back(keyCode);
		}
		keyList_mutex.unlock();
		// listening -> no hotkeys should work
		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}
	if (!hotkeysEnabled ||
		wParam == WM_KEYUP || 
		wParam == WM_SYSKEYUP ||
		// This is here purely for optimization
		!config::hasKey(keyCode)
		)
	{
 		return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
	}

	if (checkHotkeys())
	{// consume key
		return 1;
	}

#if 0
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Procedure took:" << (end - start) << "\n";
#endif // 0	
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

bool KeyListener::checkHotkeys()
{
	auto& hotkeys = config::getHotkeys();

	// hotkey checking
	for (auto& i : hotkeys)
	{
		if (!i.second.keys.empty() && std::all_of(i.second.keys.begin(), i.second.keys.end(), [](KeystrokeMessage& key) {
			return config::isKeyDown(key);
			}))
		{
			doAction(i.first);

			if (i.second.consume)
			{
				return true;
			}
			break;
			}
	}
	return false;
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
