/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** AudioDevice
*/

#pragma once

#include <openApp/Types/Scalars.hpp>

namespace oA { struct AudioDevice; }

struct oA::AudioDevice
{
    UInt channels = 0, frequency = 0, samples = 0;
};