/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Voice
*/

#include <cmath>
#include <openAudio/Voice.hpp>
#include <openAudio/Audio.hpp>

void oA::Voice::compute(UByte *buffer, Int size, const AudioDevice &device) const
{
    static constexpr int AMPLITUDE = 28000;
    auto *target = (Short *)(buffer);

    size /= 2;
    for(int i = 0; i < size; i++, _index++)
    {
        double time = static_cast<Double>(_index) / static_cast<Double>(device.frequency);
        target[i] = static_cast<Short>(AMPLITUDE * std::sin(2.0f * M_PI * 441.0f * time)); // render 441 HZ sine wave
    }
}

void oA::Voice::play(void)
{
    _play = true;
}

void oA::Voice::pause(void)
{
    _play = false;
}

void oA::Voice::stop(void)
{
    pause();
    _index = 0;
}
