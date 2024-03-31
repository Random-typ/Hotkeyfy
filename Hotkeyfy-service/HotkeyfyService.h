#pragma once
#include "../Hotkeyfy-api/Hotkeyfy.h"
#include "../Hotkeyfy-api/config.h"
#include "../Hotkeyfy-api/KeyListener.h"
#include <ranges>
#include <algorithm>

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/Hotkeyfy-api.lib")
#else
#pragma comment(lib, "../x64/Release/Hotkeyfy-api.lib")
#endif // _DEBUG

class HotkeyfyService
{
private:
	static void parseCommandLine();

public:
	static void run();
};

