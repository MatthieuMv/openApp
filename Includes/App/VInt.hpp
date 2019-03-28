/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** VInt
*/

#pragma once

#include "Value.hpp"

namespace oA { class VInt; }

class oA::VInt : public oA::Value<oA::Int>
{
public:
    using Value<Int>::Value;

    virtual const String getName(void) const noexcept { return "Int"; }
};

namespace oA
{
    const Int &ToInt(const Variant &var) { return (VGet<VInt>(var).get()); }
}