#pragma once

#include <Windows.h>
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

	static HWND hwnd;
};

