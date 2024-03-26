#pragma once
#include "../Hotkeyfy-api/Hotkeyfy.h"
#include "../Hotkeyfy-api/config.h"

#pragma comment(lib, "../x64/Debug/Hotkeyfy-api.lib")

class HotkeyfyService
{
private:
	static void parseCommandLine();

public:
	static void run();
};

