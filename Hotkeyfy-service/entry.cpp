#include "../Hotkeyfy-api/Hotkeyfy.h"

#pragma comment(lib, "../x64/Debug/Hotkeyfy-api.lib")

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