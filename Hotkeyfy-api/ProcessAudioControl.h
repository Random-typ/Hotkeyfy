#pragma once

#ifndef __ProcessAudioControl_H__
#define __ProcessAudioControl_H__

#include <string>
#include <tuple>
#include <Windows.h>
#include <audiopolicy.h>
#include <tlhelp32.h>
#include <Mmdeviceapi.h>

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "User32.lib")

class ProcessAudioControl {
public:
    ProcessAudioControl() : channel(nullptr), hwnd(NULL), pid(NULL), needsCleanup(false), autoReconnect(true) {};
    // Calls cleanup()
    ~ProcessAudioControl();

    // Select the target executable 
    // @param _exe the file name of the target e.g. L"Spotify.exe"
    void selectExecutableName(const std::wstring& _exe);

    // Manually select the target process
    // @param _hwnd the target HWND
    // @param _pid the target PID
    void selectProcess(HWND _hwnd, DWORD _pid);

    // Below documentation until prevTrack() is from msdn https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-appcommand
    // and describes how programs SHOULD interact.

    // Stop playback.
    void stop();

    // Begin playing at the current position. 
    // If already paused, it will resume.
    void play();

    // Pause. If already paused, takes no further action.
    void pause();

    // Play or pause playback.
    void playPause();

    // Go to next track.
    void nextTrack();

    // Go to previous track.
    void prevTrack();

    // Retrieve target HWND
    HWND getHWND() const;

    // @return true if the current handles are valid. 
    // E.g. the current process is running. False otherwise.
    bool isValid() const;

    // @param _value between 0.0 and 1.0
    void volumeUp(float _value);

    // @param _value between 0.0 and 1.0
    void volumeDown(float _value);

    // @param _value between 0.0 and 1.0
    void setVolume(float _value);

    // Retrieve volume level, value between 0.0 and 1.0
    float getVolume();

    // Closes open handles and resets internal variables
    void cleanup();

    // Closes open handles and opens them again (if the target process is running)
    void reconnect();
private:
    void sendMessage(int _msg);
    // checks wether the handles are still valid and 
    // tries to acquire them again if exe is not empty and autoReconnect is true
    void checkConnection();
    // releases open handles and calls CoUninitialize()
    // does not reset/change variables except channel
    void partialCleanup();

    // select the executable based on the exe variable
    void selectExecutableName();

    // select/sets the channel variable based on the pid variable
    void findChannel();

    IChannelAudioVolume* channel;

    HWND hwnd;

    DWORD pid;

    std::wstring exe;

    bool needsCleanup;

    bool autoReconnect;
};
#endif // __ProcessAudioControl_H__
