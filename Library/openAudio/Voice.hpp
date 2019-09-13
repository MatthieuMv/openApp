/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Voice
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Containers/Vector.hpp>
#include <openAudio/AudioDevice.hpp>
#include <openAudio/IEffect.hpp>

namespace oA
{
    class Voice;

    using VoicePtr = Shared<Voice>;

    class AudioDevice;
}

class oA::Voice
{
public:
    Voice(void) = default;
    virtual ~Voice(void) = default;

    virtual void compute(UByte *buffer, Int size, const AudioDevice &device) const;

    void play(void);
    void pause(void);
    void stop(void);

private:
    Vector<IEffectPtr> _effects;
    mutable UInt _index = 0;
    bool _play = false;
};