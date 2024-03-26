#include <thread>
#include "Hotkeyfy.h"
#include "config.h"
#include "resource.h"
#include <libloaderapi.h>
#include <iostream>
#include <memory.h>
#include <string>

HWND Hotkeyfy::hwnd;
HANDLE Hotkeyfy::guiProcess = NULL;

UINT const WMAPP_NOTIFYCALLBACK = WM_APP + 1;
bool Hotkeyfy::createWindows()
{
    RegisterWindowClass(L"HotkeyfyServiceClass", MAKEINTRESOURCE(IDR_MENU1), WndProc);
    RegisterWindowClass(L"HotkeyfyServiceFlyoutClass", NULL, FlyoutWndProc);

    hwnd = CreateWindowW(L"HotkeyfyServiceClass", L"Hotkeyfy", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 250, 200, NULL, NULL, GetModuleHandle(NULL), NULL);

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
        case WM_LBUTTONDOWN:
            showGUI();
            break;
        case WM_RBUTTONDOWN:
            showMenu();
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
    notify.hIcon = LoadIcon(GetModuleHandle(L"Hotkeyfy-api.dll"), MAKEINTRESOURCE(IDI_ICON1));
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

std::wstring Hotkeyfy::getBinaryPath()
{
    DWORD size = MAX_PATH;
    std::wstring path;
    path.resize(MAX_PATH);
    if (!QueryFullProcessImageNameW(GetCurrentProcess(), 0, path.data(), &size))
    {
        return std::wstring();
    }
    path.resize(size);

    return std::filesystem::path(path).parent_path().wstring();
}

void Hotkeyfy::showMenu()
{
    HMENU menu = LoadMenu(GetModuleHandle(L"Hotkeyfy-api.dll"), MAKEINTRESOURCE(IDR_MENU1));
    if (menu == NULL)
    {
        MessageBoxA(NULL, "Error", "Failed to load menu.", MB_OK | MB_ICONERROR);
        showGUI();
        return;
    }
    bool b = SetMenu(hwnd, menu);


    POINT point;
    GetCursorPos(&point);

    SetWindowPos(hwnd, HWND_TOPMOST, point.x, point.y, 10, 30, SWP_SHOWWINDOW);

    return;
    //DestroyMenu(menu);
}

void Hotkeyfy::showGUI()
{
    HANDLE hGUIprocess = NULL;
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (!pid)
        {
            return true;
        }
        HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_TERMINATE, false, pid);
        if (!process)
        {
            return true;
        }

        DWORD size = MAX_PATH;
        std::wstring path;
        path.resize(MAX_PATH);
        if (!QueryFullProcessImageNameW(process, 0, path.data(), &size))
        {
            CloseHandle(process);
            return true;
        }
        path.resize(size);

        std::wstring exeFile = std::filesystem::path(path).filename();
        if (exeFile != L"Hotkeyfy.exe")
        {
            return true;
        }

        *((HANDLE*)lParam) = process;
        SetForegroundWindow(hwnd);
        return false;
        }, (LPARAM)&hGUIprocess);

    if (GetProcessId(guiProcess))
    {
        return;
    }
    CloseHandle(guiProcess);
    guiProcess = NULL;

    if (hGUIprocess)
    {
        if (guiProcess)
        {
            CloseHandle(hGUIprocess);
            return;
        }
        if (!TerminateProcess(hGUIprocess, 0))
        {
            CloseHandle(hGUIprocess);
            return;
        }
        //DWORD code;
        //for (size_t i = 0; i < 100; i++, std::this_thread::sleep_for(std::chrono::milliseconds(20)))
        //{
        //    if (!GetExitCodeProcess(hGUIprocess, &code))
        //    {
        //        break;
        //    }
        //    if (code != STILL_ACTIVE)
        //    {
        //        break;
        //    }
        //}
        CloseHandle(hGUIprocess);
        //if (code == STILL_ACTIVE)
        //{
        //    return;
        //}
    }
    
    std::wstring GUIPath = getBinaryPath() + L"/Hotkeyfy.exe";

    SHELLEXECUTEINFOW executeInfo;
    memset(&executeInfo, 0, sizeof(executeInfo));
    executeInfo.cbSize = sizeof(executeInfo);
    executeInfo.lpFile = GUIPath.c_str();
    executeInfo.nShow = SW_SHOWNORMAL;
    executeInfo.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
    executeInfo.hwnd = hwnd;
    std::wstring wLaunch(config::launchedFromService.begin(), config::launchedFromService.begin());
    executeInfo.lpParameters = wLaunch.c_str();

    if (!ShellExecuteExW(&executeInfo)) {
        return;
    }
    guiProcess = executeInfo.hProcess; 
}

void Hotkeyfy::waitForGUI()
{
    if (!guiProcess)
    {
        return;
    }
    WaitForSingleObject(guiProcess, INFINITE);
    CloseHandle(guiProcess);
    guiProcess = NULL;
}

void Hotkeyfy::sendLaunchGUI()
{
    bool found = false;
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (!pid)
        {
            return true;
        }
        HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_TERMINATE, false, pid);
        if (!process)
        {
            return true;
        }

        DWORD size = MAX_PATH;
        std::wstring path;
        path.resize(MAX_PATH);
        if (!QueryFullProcessImageNameW(process, 0, path.data(), &size))
        {
            CloseHandle(process);
            return true;
        }
        CloseHandle(process);
        path.resize(size);

        std::wstring exeFile = std::filesystem::path(path).filename();
        if (exeFile != L"Hotkeyfy-service.exe")
        {
            return true;
        }
        *(bool*)(lParam) = true;

        //SendMessageA(hwnd, );

        return false;
        }, (LPARAM)&found);

    std::wstring ServicePath = getBinaryPath() + L"/Hotkeyfy-service.exe";

    SHELLEXECUTEINFOW executeInfo;
    memset(&executeInfo, 0, sizeof(executeInfo));
    executeInfo.cbSize = sizeof(executeInfo);
    executeInfo.lpFile = ServicePath.c_str();
    executeInfo.nShow = SW_HIDE;
    executeInfo.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
    executeInfo.hwnd = hwnd;

    std::wstring wLaunch(config::launchedFromService.begin(), config::launchedFromService.begin());
    executeInfo.lpParameters = wLaunch.c_str();

    if (!ShellExecuteExW(&executeInfo)) {
        return;
    }
}

