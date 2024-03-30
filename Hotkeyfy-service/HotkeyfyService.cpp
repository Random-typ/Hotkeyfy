#include "HotkeyfyService.h"

void HotkeyfyService::parseCommandLine()
{
	std::string cml = GetCommandLineA();

	auto view = cml | std::views::split(' ');

	if (std::ranges::any_of(view, [](const std::string_view _param){
		return _param == config::launchedFromService || _param == config::showGUI;
		}))
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
