#include "HotkeyfyService.h"

void HotkeyfyService::parseCommandLine()
{
	std::string cml = GetCommandLineA();

	std::vector<std::string> paramList;

	for (size_t start = 0, end = 0;;)
	{
		
		end = cml.find(" ", start + 1);
		paramList.emplace_back(cml.substr(start, end - start));

		if (end == std::string::npos || end >= cml.size() - 1)
		{
			break;
		}
		start = end;
	}
	

	if (paramList.size() > 1 && paramList[1] == config::launchedFromService)
	{

	}
}

void HotkeyfyService::run()
{
	parseCommandLine();

	Hotkeyfy::createWindows();
	Sleep(100);
	Hotkeyfy::addToSystemTray();
}
