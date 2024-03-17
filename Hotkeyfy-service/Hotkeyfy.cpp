#include "Hotkeyfy.h"

bool Hotkeyfy::createGhostWindow()
{
    HWND dummyHWND = ::CreateWindowA("Hotkeyfy_class", "Hotkeyfy", WS_VISIBLE, 0, 0, 100, 100, NULL, NULL, NULL, NULL);
    return false;
}

bool Hotkeyfy::addToSystemTray()
{
    NOTIFYICONDATA notify;
    memset(&notify, 0, sizeof(NOTIFYICONDATAA));
    notify.cbSize = sizeof(NOTIFYICONDATAA);
    notify.hWnd = getProcessWindow();
    notify.uFlags;
    notify.uCallbackMessage;
    notify.hIcon;
    const char tooltip[] = "Hotkeyfy";
    memcpy_s(notify.szTip, sizeof(notify.szTip), tooltip, sizeof(tooltip));
    notify.dwState;// unused
    notify.dwStateMask;// unused
    notify.szInfo;// unused
    notify.uVersion;// unused
    notify.dwInfoFlags;// unused
    notify.guidItem;
    notify.hBalloonIcon;// unused
    
    if (!Shell_NotifyIcon(NIM_ADD, &notify))
    {
        std::cout << "asd";
    };
    while (true)
    {

    }
    return false;
}

HWND Hotkeyfy::getProcessWindow()
{
    HWND hwnd = NULL;
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid == GetCurrentProcessId())
        {
            *(HWND*)lParam = hwnd;
            return false;
        }
        return true;
        }, (LPARAM)&hwnd);
    return hwnd;
}
