#include "Hotkeyfy.h"

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
	Hotkeyfy::createWindows();
	Sleep(100);
	Hotkeyfy::addToSystemTray();

}