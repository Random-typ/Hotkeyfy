#include "Hotkeyfy.h"
#include <filesystem>

namespace Hotkeyfy {

    HWND Hotkeyfy::hwnd;
    HANDLE Hotkeyfy::guiProcess = NULL;
    std::thread Hotkeyfy::waitForGUIth;

    UINT const WMAPP_NOTIFYCALLBACK = WM_APP + 1;
    bool Hotkeyfy::createWindows()
    {
        if (findServiceWindow())
        {
            std::cout << "HotkeyfyServiceClass class already registered\n";
            terminateSelf();
        }
        RegisterWindowClass(L"HotkeyfyServiceClass", NULL, WndProc);

        hwnd = CreateWindowW(L"HotkeyfyServiceClass", L"HotkeyfyService", WS_EX_TOOLWINDOW,
            CW_USEDEFAULT, 0, 250, 200, NULL, NULL, GetModuleHandle(NULL), NULL);

        return hwnd;
    }

    LRESULT CALLBACK Hotkeyfy::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case showGUIMSG:
            showGUI(true);
            break;
        case WM_CREATE:
            break;
        case WM_QUIT:
            break;
        case WMAPP_NOTIFYCALLBACK:
            switch (lParam)
            {
            case WM_LBUTTONDOWN:
                showGUI(true);
                break;
            case WM_RBUTTONDOWN:
                showMenu();
                break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(hwnd, message, wParam, lParam);
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
        std::cout << "add to system tray\n";
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
            // "Shell_NotifyIcon() failed\n";
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

    HWND Hotkeyfy::findServiceWindow()
    {
        return FindWindow(L"HotkeyfyServiceClass", NULL);
    }

    HWND Hotkeyfy::findDesktopWindow()
    {
        HWND window = NULL;
        BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
            {
                
                DWORD processId;
                if (!GetWindowThreadProcessId(hwnd, &processId))
                {
                    // Continue enumerating
                    return TRUE;
                }
                std::wstring windowTitle;
                windowTitle.resize(MAX_PATH);
                windowTitle.resize(GetWindowTextW(hwnd, (wchar_t*)windowTitle.data(), windowTitle.size()));
                if (windowTitle != L"Hotkeyfy")
                {
                    return TRUE;
                }

                HANDLE proc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, processId);
                if (!proc)
                {
                    return TRUE;
                }
                std::wstring path;
                path.resize(MAX_PATH);
                path.resize(GetProcessImageFileNameW(proc, (wchar_t*)path.data(), path.size()));
                if (path.empty())
                {
                    return TRUE;
                }
                if (std::filesystem::path(path).filename() != L"Hotkeyfy.exe")
                {
                    return TRUE;
                }
                HWND* window = (HWND*)(lParam);
                *window = hwnd;
                return FALSE;
            }, (LPARAM)&window);

        return window;
    }

    std::wstring Hotkeyfy::getBinaryPath()
    {
        DWORD size = MAX_PATH;
        std::wstring path;
        path.resize(MAX_PATH);
        if (!QueryFullProcessImageNameW(GetCurrentProcess(), 0, (wchar_t*)path.data(), &size))
        {
            return std::wstring();
        }
        path.resize(size);

        return std::filesystem::path(path).parent_path().wstring();
    }

    void Hotkeyfy::showMenu()
    {
        POINT point;
        GetCursorPos(&point);

        SetWindowPos(hwnd, HWND_TOPMOST, point.x, point.y, 0, 0, WS_EX_TOOLWINDOW);

        HMENU hmenu = CreatePopupMenu();
        MENUITEMINFOA itemInfo{0};
        itemInfo.cbSize = sizeof(itemInfo);
        itemInfo.fMask = MIIM_STRING | MIIM_ID;
        itemInfo.fType = MFT_STRING;
        itemInfo.fState = MFS_DEFAULT;
        itemInfo.wID = IDM_SHOW;
        itemInfo.hSubMenu = hmenu;
        itemInfo.hbmpChecked = NULL;
        itemInfo.hbmpUnchecked = NULL;
        itemInfo.dwItemData = NULL;
        itemInfo.dwTypeData = (char*)"Show";
        itemInfo.cch = strlen(itemInfo.dwTypeData);
        itemInfo.hbmpItem = NULL;

        InsertMenuItemA(hmenu, 0, true, &itemInfo);

        itemInfo.wID = IDM_EXIT;
        itemInfo.dwTypeData = (char*)"Exit";
        itemInfo.cch = strlen(itemInfo.dwTypeData);

        InsertMenuItemA(hmenu, 1, true, &itemInfo);

        SetForegroundWindow(hwnd);
        DrawMenuBar(hwnd);

        POINT pt;
        GetCursorPos(&pt);
        int identifier = TrackPopupMenu(hmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN | TPM_RETURNCMD, pt.x, pt.y, 0, hwnd, NULL);

        switch (identifier)
        {
        case IDM_SHOW:
            ShowWindow(hwnd, SW_HIDE);
            showGUI(true);
            break;
        case IDM_EXIT:
            terminateHotkeyfy();
            break;
        }
    }

    void Hotkeyfy::showGUI(bool _wait)
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
            CloseHandle(hGUIprocess);
        }

        std::wstring GUIPath = getBinaryPath() + L"/Hotkeyfy.exe";

        SHELLEXECUTEINFOW executeInfo;
        memset(&executeInfo, 0, sizeof(executeInfo));
        executeInfo.cbSize = sizeof(executeInfo);
        executeInfo.lpFile = GUIPath.c_str();
        executeInfo.nShow = SW_SHOWNORMAL;
        executeInfo.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
        executeInfo.hwnd = hwnd;
        std::wstring wLaunch(config::launchedFromService.begin(), config::launchedFromService.end());
        executeInfo.lpParameters = wLaunch.c_str();

        if (!ShellExecuteExW(&executeInfo)) {
            return;
        }
        guiProcess = executeInfo.hProcess;

        if (_wait)
        {
            if (waitForGUIth.joinable())
            {
                waitForGUIth.join();
            }
            waitForGUIth = std::thread(waitForGUI);
        }
    }

    void Hotkeyfy::waitForGUI()
    {
        if (!guiProcess)
        {
            return;
        }
        KeyListener::disableHotkeys();
        WaitForSingleObject(guiProcess, INFINITE);
        CloseHandle(guiProcess);
        KeyListener::enableHotkeys();
        config::reload();
        guiProcess = NULL;
    }

    bool Hotkeyfy::sendLaunchGUI()
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

            SendMessageA(hwnd, showGUIMSG, 0, 0);

            return false;
            }, (LPARAM)&found);

        if (found)
        {
            return true;
        }

        std::wstring ServicePath = getBinaryPath() + L"/Hotkeyfy-service.exe";

        SHELLEXECUTEINFOW executeInfo;
        memset(&executeInfo, 0, sizeof(executeInfo));
        executeInfo.cbSize = sizeof(executeInfo);
        executeInfo.lpFile = ServicePath.c_str();
        executeInfo.nShow = SW_SHOW;
        executeInfo.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
        executeInfo.hwnd = hwnd;

        std::wstring wLaunch(config::launchedFromService.begin(), config::launchedFromService.end());
        executeInfo.lpParameters = wLaunch.c_str();

        if (!ShellExecuteExW(&executeInfo)) {
            return false;
        }
        return true;
    }

    void Hotkeyfy::loadConfig()
    {
        std::cout << "loading config\n";
        std::wstring path;
        path.resize(MAX_PATH);
        SHGetSpecialFolderPathW(NULL, path.data(), CSIDL_APPDATA, true);
        path.resize(wcslen(path.c_str()));

        config::load(path + L"/Hotkeyfy/config.json");
    }

    void Hotkeyfy::terminateHotkeyfy()
    {
        std::cout << "terminating hotkeyfy...\n";
        if (guiProcess)
        {
            TerminateProcess(guiProcess, 0);
        }

        HWND hwnd = findDesktopWindow();
        if (hwnd)
        {
            DWORD pid;
            GetWindowThreadProcessId(hwnd, &pid);
            const HANDLE hotkeyfyGUI = OpenProcess(PROCESS_TERMINATE, false, pid);
            if (hotkeyfyGUI)
            {
                TerminateProcess(hotkeyfyGUI, 0);
                CloseHandle(hotkeyfyGUI);
            }
        }

        terminateSelf();
    }

    void Hotkeyfy::terminateSelf()
    {
        std::cout << "terminating self.\n";
        // this is the most reliable way i found, to close the current process
        TerminateProcess(GetCurrentProcess(), 0);
    }

}