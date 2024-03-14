#include "pch.h"
#include "ProcessAudioControl.h"

ProcessAudioControl::~ProcessAudioControl()
{
    cleanup();
}

void ProcessAudioControl::selectExecutableName(const std::wstring& _exe)
{
    exe = _exe;
    selectExecutableName();
}

void ProcessAudioControl::setVolume(float _value)
{
    if (_value < 0.0)
    {
        _value = 0.0;
    }
    if (_value > 1.0)
    {
        _value = 1.0;
    }

    findChannel();
    if (!channel)
    {
        return;
    }
    // set volume on all channels
    // channels here refer to speakers e.g. left speaker right speaker
    UINT32 count = 0;
    channel->GetChannelCount(&count);
    for (size_t i = 0; i < count; i++)
    {
        channel->SetChannelVolume(i, _value, NULL);
    }
}

float ProcessAudioControl::getVolume()
{
    findChannel();
    if (!channel)
    {
        return 0;
    }

    float max = 0;
    UINT32 count = 0;
    channel->GetChannelCount(&count);
    for (size_t i = 0; i < count; i++)
    {
        float volume = 0;
        channel->GetChannelVolume(i, &volume);
        if (volume > max)
        {
            max = volume;
        }
    }
    return max;
}

void ProcessAudioControl::cleanup()
{
    hwnd = NULL;
    pid = NULL;
    partialCleanup();
}

void ProcessAudioControl::reconnect()
{
    partialCleanup();

    selectExecutableName();
}

void ProcessAudioControl::sendMessage(int _msg)
{
    checkConnection();
    PostMessage(hwnd, WM_APPCOMMAND, 0, MAKELONG(0, _msg));
}

void ProcessAudioControl::checkConnection()
{
    if (!autoReconnect || isValid())
    {
        return;
    }

    reconnect();
}

void ProcessAudioControl::partialCleanup()
{
    if (channel)
    {
        channel->Release();
        channel = nullptr;
    }
    if (!needsCleanup)
    {
        return;
    }
    CoUninitialize();
    needsCleanup = false;
}

void ProcessAudioControl::selectExecutableName()
{
    cleanup();
    if (exe.empty())
    {
        return;
    }
    std::tuple<HWND, std::wstring, DWORD> params = { 0, exe, 0 };

    // Enumerate the windows using a lambda to process each window
    BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
        {
            std::tuple<HWND, std::wstring, DWORD>* param = (std::tuple<HWND, std::wstring, DWORD>*)lParam;
            DWORD pid;
            GetWindowThreadProcessId(hwnd, &pid);
            if (!IsWindowVisible(hwnd))
            {
                return true;
            }

            HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
            if (!proc)
            {
                return true;
            }

            wchar_t path[MAX_PATH];
            DWORD len = MAX_PATH;
            QueryFullProcessImageName(proc, 0, path, &len);

            CloseHandle(proc);

            wchar_t* fileName = 0;
            for (size_t i = 0; ; i++)
            {
                if (path[i] == '\0')
                {
                    break;
                }
                if (path[i] == '\\')
                {
                    fileName = &path[i + 1];
                }
            }

            if (!fileName || wcslen(fileName) != std::get<1>(*param).size() || memcmp(std::get<1>(*param).c_str(), fileName, std::get<1>(*param).size()))
            {
                return true;
            }
            std::get<0>(*param) = hwnd;
            std::get<2>(*param) = pid;
            return false;
        }, (LPARAM)&params);

    hwnd = std::get<0>(params);
    pid = std::get<2>(params);
}

void ProcessAudioControl::findChannel()
{
    checkConnection();
    if (channel)
    {
        return;
    }


    HRESULT hr = S_OK;
    if (!needsCleanup)
    {
        hr = CoInitialize(NULL);
    }
    if (hr != S_OK)
    {
        return;
    }

    needsCleanup = true;

    IMMDeviceEnumerator* deviceEnumerator = NULL;
    IMMDevice* defaultDevice = NULL;
    IAudioSessionManager2* sessionManager = NULL;

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&deviceEnumerator);
    if (hr != S_OK)
    {
        return;
    }
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    if (hr != S_OK)
    {
        return;
    }
    hr = defaultDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&sessionManager);
    if (hr != S_OK)
    {
        deviceEnumerator->Release();
        return;
    }

    IAudioSessionEnumerator* audioEnum;

    hr = sessionManager->GetSessionEnumerator(&audioEnum);
    if (hr != S_OK)
    {
        defaultDevice->Release();
        deviceEnumerator->Release();
        return;
    }

    int count = 0;
    hr = audioEnum->GetCount(&count);
    if (hr != S_OK)
    {
        sessionManager->Release();
        defaultDevice->Release();
        deviceEnumerator->Release();
        return;
    }


    for (size_t i = 0; i < count; i++)
    {
        IAudioSessionControl* session;
        hr = audioEnum->GetSession(i, &session);
        if (hr != S_OK)
        {
            continue;
        }

        IAudioSessionControl2* session2;
        hr = session->QueryInterface(__uuidof(IAudioSessionControl2), (void**)&session2);
        if (hr != S_OK)
        {
            session->Release();
            continue;
        }

        DWORD id;
        session2->GetProcessId(&id);

        if (id == pid)

        {
            hr = session2->QueryInterface(__uuidof(IChannelAudioVolume), (LPVOID*)&channel);
            if (hr != S_OK)
            {
                channel = nullptr;
                continue;
            }
            session->Release();
            session2->Release();
            break;
        }

        session->Release();
        session2->Release();
    }

    audioEnum->Release();
    sessionManager->Release();
    defaultDevice->Release();
    deviceEnumerator->Release();
}

void ProcessAudioControl::selectProcess(HWND _hwnd, DWORD _pid)
{
    hwnd = _hwnd;
    pid = _pid;
    autoReconnect = false;
}

void ProcessAudioControl::stop()
{
    sendMessage(APPCOMMAND_MEDIA_STOP);
}

void ProcessAudioControl::play()
{
    sendMessage(APPCOMMAND_MEDIA_PLAY);
}

void ProcessAudioControl::pause()
{
    sendMessage(APPCOMMAND_MEDIA_PAUSE);
}

void ProcessAudioControl::playPause()
{
    sendMessage(APPCOMMAND_MEDIA_PLAY_PAUSE);
}

void ProcessAudioControl::nextTrack()
{
    sendMessage(APPCOMMAND_MEDIA_NEXTTRACK);
}

void ProcessAudioControl::prevTrack()
{
    sendMessage(APPCOMMAND_MEDIA_PREVIOUSTRACK);
}

HWND ProcessAudioControl::getHWND() const
{
    return hwnd;
}

bool ProcessAudioControl::isValid() const
{
    return IsWindowVisible(hwnd);
}

void ProcessAudioControl::volumeUp(float _value)
{
    setVolume(getVolume() + _value);
}

void ProcessAudioControl::volumeDown(float _value)
{
    setVolume(getVolume() - _value);
}
