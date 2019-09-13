/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Audio
*/

#include <SDL2/SDL.h>
#include <openApp/Types/Error.hpp>
#include <openAudio/Audio.hpp>
#include <openApp/Core/Log.hpp>

oA::Audio oA::Audio::AudioInitializer;
oA::Mutex oA::Audio::AudioMutex;

void oA::Audio::Initialize(UInt channels, UInt frequency, UInt samples)
{
    UniqueLock lock(AudioMutex);

    SDL_InitSubSystem(SDL_INIT_AUDIO);
    AudioInitializer.openDevice(channels, frequency, samples);
}

void oA::Audio::Play(const String &path)
{
    UniqueLock lock(AudioMutex);

    AudioInitializer.play(path);
}

oA::VoicePtr oA::Audio::OpenVoice(void)
{
    UniqueLock lock(AudioMutex);

    return AudioInitializer.openVoice();
}

void oA::Audio::SetChannels(UInt channels)
{
    UniqueLock lock(AudioMutex);

    AudioInitializer.setChannels(channels);
}

void oA::Audio::SetFrequency(UInt frequency)
{
    UniqueLock lock(AudioMutex);

    AudioInitializer.setFrequency(frequency);
}

void oA::Audio::SetSamples(UInt samples)
{
    UniqueLock lock(AudioMutex);

    AudioInitializer.setSamples(samples);
}

void oA::Audio::AudioCallback(void *userdata, UByte *buffer, Int size)
{
    UniqueLock lock(AudioMutex);
    Vector<VoicePtr> *voices = (Vector<VoicePtr> *)(userdata);

    voices->removeIf([buffer, size](const VoicePtr &voice) {
        if (voice.unique())
            return true;
        voice->compute(buffer, size, AudioInitializer._device);
        return false;
    });
}

oA::Audio::Audio(void)
{
}

oA::Audio::~Audio(void)
{
    closeDevice();
    SDL_CloseAudio();
}

void oA::Audio::openDevice(UInt channels, UInt frequency, UInt samples)
{
    SDL_AudioSpec want, have;

    SDL_memset(&want, 0, sizeof(want));
    SDL_memset(&have, 0, sizeof(have));
    want.freq = frequency;
    want.format = AUDIO_S16SYS;
    want.channels = channels;
    want.samples = samples;
    want.callback = &Audio::AudioCallback;
    want.userdata = &_voices;
    if (SDL_OpenAudio(&want, &have) != 0)
        throw RuntimeError("Audio", SDL_GetError());
    if (want.format != have.format)
        throw RuntimeError("Audio", SDL_GetError());
    _device.channels = have.channels;
    _device.frequency = have.freq;
    _device.samples = have.samples;
    SDL_PauseAudio(0);
}

void oA::Audio::closeDevice(void)
{
    SDL_PauseAudio(1);
    if (_deviceID)
        SDL_CloseAudioDevice(_deviceID);
    _deviceID = 0;
}

void oA::Audio::updateDevice(void)
{
    openDevice(_device.channels, _device.frequency, _device.samples);
}

void oA::Audio::play(const String &path)
{
    auto it = _files.find(path);

    if (it == _files.end())
        return; //loadFile();
    it->second.play();
}

oA::VoicePtr oA::Audio::openVoice(void)
{
    return _voices.emplace_back(std::make_shared<Voice>());
}

void oA::Audio::setChannels(UInt channels)
{
    _device.channels = channels;
    updateDevice();
}

void oA::Audio::setFrequency(UInt frequency)
{
    _device.frequency = frequency;
    updateDevice();
}

void oA::Audio::setSamples(UInt samples)
{
    _device.samples = samples;
    updateDevice();
}
