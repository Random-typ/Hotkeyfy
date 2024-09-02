#include "HotkeyfyService.h"
#include <iostream>
#ifdef _DEBUG
int main()
#else
int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
#endif // !_DEBUG
{
	Hotkeyfy::Hotkeyfy::findDesktopWindow();
	HotkeyfyService::run();
}