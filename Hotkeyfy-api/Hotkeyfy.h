#pragma once

#include <Shlobj.h>

#include "config.h"
#include "resource.h"
#include "KeyListener.h"
#include "HotkeyfyExport.h"

namespace Hotkeyfy {
class HOTKEYFYAPI_DECLSPEC Hotkeyfy
{
public:
	static void RegisterWindowClass(PCWSTR pszClassName, PCWSTR pszMenuName, WNDPROC lpfnWndProc);

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	static bool createWindows();

	static bool addToSystemTray();

	static HWND getProcessWindow();

	// gets current process binary location directory
	static std::wstring getBinaryPath();

	static void showMenu();

	static void showGUI(bool _wait);

	// blocks until GUI is closed if it is running
	static void waitForGUI();

	// sends a message to the service who then calls showGUI()
	// if the service is not running it is started
	static void sendLaunchGUI();

	static void loadConfig();

	static void terminateHotkeyfy();

	static constexpr const UINT showGUIMSG = WM_USER + 10;

	static HWND hwnd;

	static HANDLE guiProcess;

	static std::thread waitForGUIth;

	static constexpr const int IDM_EXIT = 100;
	static constexpr const int IDM_SHOW = 101;
};
}