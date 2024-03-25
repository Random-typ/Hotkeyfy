#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <filesystem>
#include <iostream>


class Hotkeyfy
{
public:
	static void RegisterWindowClass(PCWSTR pszClassName, PCWSTR pszMenuName, WNDPROC lpfnWndProc);

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK FlyoutWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static bool createWindows();

	static bool addToSystemTray();

	static HWND getProcessWindow();


	static void showGUI();

	// blocks until GUI is closed if it is running
	static void waitForGUI();

	static HWND hwnd;

	static HANDLE guiProcess;
};

