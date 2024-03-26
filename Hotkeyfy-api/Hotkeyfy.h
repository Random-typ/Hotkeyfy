#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <filesystem>
#include <iostream>
#include "HotkeyfyExport.h"


class HOTKEYFYAPI_DECLSPEC Hotkeyfy
{
public:
	static void RegisterWindowClass(PCWSTR pszClassName, PCWSTR pszMenuName, WNDPROC lpfnWndProc);

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK FlyoutWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static bool createWindows();

	static bool addToSystemTray();

	static HWND getProcessWindow();

	// gets current process binary location directory
	static std::wstring getBinaryPath();

	static void showMenu();

	static void showGUI();

	// blocks until GUI is closed if it is running
	static void waitForGUI();

	// sends a message to the service who then calls showGUI()
	// if the service is not running it willbe started
	static void sendLaunchGUI();

	static HWND hwnd;

	static HANDLE guiProcess;
};

