#include "Hotkeyfy.h"
#include "resource.h"

HWND Hotkeyfy::hwnd;

UINT const WMAPP_NOTIFYCALLBACK = WM_APP + 1;
bool Hotkeyfy::createWindows()
{
    RegisterWindowClass(L"HotkeyfyServiceClass", MAKEINTRESOURCE(IDR_MENU1), WndProc);
    RegisterWindowClass(L"HotkeyfyServiceFlyoutClass", NULL, FlyoutWndProc);

    hwnd = CreateWindowW(L"HotkeyfyServiceClass", L"Hotkeyfy", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 250, 200, NULL, NULL, GetModuleHandle(NULL), NULL);
    //ShowWindow(hwnd, SW_SHOW);

    //hwnd = CreateWindowA("STATIC", "Hotkeyfy", 0, 0, 0, 100, 100, NULL, NULL, NULL, NULL);
    return hwnd;
}

LRESULT CALLBACK Hotkeyfy::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND s_hwndFlyout = NULL;
    static BOOL s_fCanShowFlyout = TRUE;

    switch (message)
    {
    case WM_CREATE:


        break;
    case WMAPP_NOTIFYCALLBACK:
        switch (lParam)
        {
        case NIN_SELECT:
            std::cout << "open\n";
            break;
        case WM_CONTEXTMENU:
            std::cout << "context\n";
            break;
        default:
            break;
        }
        
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK Hotkeyfy::FlyoutWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::cout << message;
    switch (message)
    {
    case WM_PAINT:
    {
        //// paint a pretty picture
        //PAINTSTRUCT ps;
        //HDC hdc = BeginPaint(hwnd, &ps);
        //FlyoutPaint(hwnd, hdc);
        //EndPaint(hwnd, &ps);
    }
    break;
    case WM_ACTIVATE:
        if (LOWORD(wParam) == WA_INACTIVE)
        {
            // when the flyout window loses focus, hide it.
            //PostMessage(GetParent(hwnd), WMAPP_HIDEFLYOUT, 0, 0);
        }
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void Hotkeyfy::RegisterWindowClass(PCWSTR pszClassName, PCWSTR pszMenuName, WNDPROC lpfnWndProc)
{
    WNDCLASSEX wcex = { sizeof(wcex) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = lpfnWndProc;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = pszMenuName;
    wcex.lpszClassName = pszClassName;
    RegisterClassEx(&wcex);
}


bool Hotkeyfy::addToSystemTray()
{
    NOTIFYICONDATA notify;
    memset(&notify, 0, sizeof(NOTIFYICONDATAA));
    notify.cbSize = sizeof(NOTIFYICONDATAA);
    notify.hWnd = hwnd;
    notify.uFlags = NIF_ICON | NIF_MESSAGE;
    notify.uCallbackMessage = WMAPP_NOTIFYCALLBACK;
    notify.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
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
        std::cout << "Shell_NotifyIcon() failed\n";
    }
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
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
