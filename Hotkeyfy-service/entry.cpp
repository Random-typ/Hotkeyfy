#include "Hotkeyfy.h"

#ifdef _DEBUGg
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
	Hotkeyfy::addToSystemTray();

}