#include "HotkeyfyService.h"

void HotkeyfyService::parseCommandLine()
{
	std::string cml = GetCommandLineA();

	std::vector<std::string> paramList;

	for (size_t start = 0, end = 0;;)
	{
		
		end = cml.find(" ", start);
		paramList.emplace_back(cml.substr(start, end - start));

		if (end == std::string::npos || end >= cml.size() - 1)
		{
			break;
		}
		start = end + 1;
	}
	
	if (paramList.size() > 1 && paramList[1] == config::launchedFromService)
	{
		Hotkeyfy::Hotkeyfy::showGUI(true);
	}
	else if (FindWindow(NULL, L"Hotkeyfy"))
	{
		Hotkeyfy::Hotkeyfy::showGUI(true);
	}
}

void HotkeyfyService::run()
{
	parseCommandLine();

	Hotkeyfy::Hotkeyfy::createWindows();

	Hotkeyfy::Hotkeyfy::loadConfig();

	KeyListener::init();
	KeyListener::enableHotkeys();

	Hotkeyfy::Hotkeyfy::addToSystemTray();
}
