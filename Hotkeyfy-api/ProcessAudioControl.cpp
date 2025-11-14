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
    if (channels.empty())
    {
        return;
    }
    // set volume on all channels
    // channels here refer to speakers e.g. left speaker right speaker
    UINT32 count = 0;
    for (auto& channel : channels)
    {
        channel->GetChannelCount(&count);
        for (size_t i = 0; i < count; i++)
        {
            channel->SetChannelVolume(i, _value, NULL);
        }
    }
}

float ProcessAudioControl::getVolume()
{
    findChannel();
    if (channels.empty())
    {
        return 0;
    }

    // find max volume
    float max = 0;
    UINT32 count = 0;
    for (auto& channel : channels)
    {
        channel->GetChannelCount(&count);
        for (size_t i = 0; i < count; i++)
        {
            float volume = 0;
            channel->GetChannelVolume(i, &volume);
            max = std::max(max, volume);
        }
    }
    return max;
}

void ProcessAudioControl::cleanup()
{
    hwnd = NULL;
    PIDs.clear();
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
    if (!channels.empty())
    {
        for (auto& channel : channels)
        {
            channel->Release();
        }
        channels.clear();
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
    
    std::tuple<HWND*, std::wstring> params = { &hwnd, exe };
    // Enumerate the windows using a lambda to process each window
    BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
        {
            std::tuple<HWND*, std::wstring>* param = (std::tuple<HWND*, std::wstring>*)lParam;
            DWORD pid;
            if (!IsWindowVisible(hwnd))
            {
                return true;
            }
            GetWindowThreadProcessId(hwnd, &pid);

            if (!matchProcess(std::get<1>(*param), pid))
            {
                return true;
            }

            if (!*std::get<0>(*param))
            {
                *std::get<0>(*param) = hwnd;
            }

            return false;
        }, (LPARAM)&params);

    std::vector<DWORD> processes;
    processes.resize(64);

    DWORD size = 0;
    while (processes.size() <= size || !size)
    {
        EnumProcesses(processes.data(), processes.size() * sizeof(DWORD), &size);
        processes.resize(processes.size() + 64);
    }
    processes.resize(size);

    for (auto& pid : processes)
    {
        if (ProcessAudioControl::matchProcess(exe, pid))
        {
            PIDs.push_back(pid);
        }
    }
}

void ProcessAudioControl::findChannel()
{
    checkConnection();
    if (!channels.empty())
    {
        return;
    }


    HRESULT hr = S_OK;
    if (!needsCleanup)
    {
        hr = CoInitialize(NULL);
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

        if (std::any_of(PIDs.begin(), PIDs.end(), [&id](DWORD pid){ return pid == id; }))
        {
            IChannelAudioVolume*& channel = channels.emplace_back();
            hr = session2->QueryInterface(__uuidof(IChannelAudioVolume), (LPVOID*)&channel);
            if (hr == S_OK)
            {
                channels.push_back(channel);
            }
        }

        session->Release();
        session2->Release();
    }

    audioEnum->Release();
    sessionManager->Release();
    defaultDevice->Release();
    deviceEnumerator->Release();
}

bool ProcessAudioControl::matchProcess(const std::wstring& exe, DWORD pid)
{
    HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
    if (!proc)
    {
        return false;
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

    if (!fileName || wcslen(fileName) != exe.size() || memcmp(exe.c_str(), fileName, exe.size()))
    {
        return false;
    }
    return true;
}

void ProcessAudioControl::selectProcess(HWND _hwnd, DWORD _pid)
{
    if (_hwnd)
    {
        hwnd = _hwnd;
    }
    PIDs.push_back(_pid);
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
