/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** VFloat
*/

#pragma once

#include "Value.hpp"

namespace oA { class VFloat; }

class oA::VFloat : public oA::Value<oA::Float>
{
public:
    using Value<Float>::Value;

    virtual const String getName(void) const noexcept { return "Float"; }
};

namespace oA
{
    const Float &ToFloat(const Variant &var) { return (VGet<VFloat>(var).get()); }
}