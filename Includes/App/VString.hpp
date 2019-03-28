/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** VString
*/

#pragma once

#include "Value.hpp"

namespace oA { class VString; }

class oA::VString : public oA::Value<oA::String>
{
public:
    using Value<String>::Value;

    virtual const String getName(void) const noexcept { return "String"; }
};

namespace oA
{
    const String &ToString(const Variant &var) { return (VGet<VString>(var).get()); }
}