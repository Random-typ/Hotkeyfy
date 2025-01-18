#include "HotkeyfyService.h"

void HotkeyfyService::parseCommandLine()
{
	std::cout << "parse command line\n";
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
	
	if (std::any_of(paramList.begin(), paramList.end(), [](auto _param) { return _param == config::uninstall; }))
	{// uninstall called -> reset audio settings and exit all.

		// reset volume
		Hotkeyfy::Hotkeyfy::loadConfig();
		KeyListener::reloadConfig();
		KeyListener::audioControl.setVolume(1);

		Hotkeyfy::Hotkeyfy::terminateHotkeyfy();
		exit(0);
		return;
	}

	if (std::any_of(paramList.begin(), paramList.end(), [](const std::string& _param){
		return _param == config::launchedFromService || _param == config::showGUI;
		}) || Hotkeyfy::Hotkeyfy::findDesktopWindow())
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
