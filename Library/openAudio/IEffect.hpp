/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IEffect
*/

#pragma once

#include <openApp/Types/Memory.hpp>

namespace oA
{
    class IEffect;

    using IEffectPtr = Unique<IEffect>;
}

class oA::IEffect
{
public:
    virtual ~IEffect(void) = default;
};