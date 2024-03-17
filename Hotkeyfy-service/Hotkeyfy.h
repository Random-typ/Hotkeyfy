#pragma once

#include <Windows.h>
#include <iostream>

class Hotkeyfy
{
public:
	static bool createGhostWindow();

	static bool addToSystemTray();

	static HWND getProcessWindow();

	static HWND hwnd;
};

