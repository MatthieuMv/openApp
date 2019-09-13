/*
** EPITECH PROJECT, 2019

void SetChannels(UInt channels);
void SetFrequency(UInt frequency);
void SetSamples(UInt samples);
** openApp
** File description:
** Audio
*/

#pragma once

#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Mutex.hpp>
#include <openAudio/Voice.hpp>
#include <SDL2/SDL_audio.h>

#ifndef DEFAULT_CHANNELS
    #define DEFAULT_CHANNELS 1
#endif

#ifndef DEFAULT_FREQUENCY
    #define DEFAULT_FREQUENCY 48000
#endif

#ifndef DEFAULT_SAMPLES
    #define DEFAULT_SAMPLES 4096
#endif

namespace oA { class Audio; }

class oA::Audio
{
public:
    static void Initialize(UInt channels = DEFAULT_CHANNELS, UInt frequency = DEFAULT_FREQUENCY, UInt samples = DEFAULT_SAMPLES);

    static void Play(const String &path);

    static VoicePtr OpenVoice(void);

    static void SetChannels(UInt channels);
    static void SetFrequency(UInt frequency);
    static void SetSamples(UInt samples);

private:
    static void AudioCallback(void *userdata, UByte *buffer, Int size);

    static Audio AudioInitializer;
    static Mutex AudioMutex;

    UMap<String, Voice> _files;
    Vector<VoicePtr>    _voices;
    AudioDevice         _device;
    UInt                _deviceID = 0;

    Audio(void);
    ~Audio(void);

    void openDevice(UInt channels, UInt frequency, UInt samples);
    void closeDevice(void);
    void updateDevice(void);

    void play(const String &path);
    VoicePtr openVoice(void);

    void setChannels(UInt channels);
    void setFrequency(UInt frequency);
    void setSamples(UInt samples);
};