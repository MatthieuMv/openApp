/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Colors
*/

#pragma once

// Scalars
#include "Core/Scalar.hpp"
// String
#include "Core/String.hpp"

namespace oA { class Color; }

class oA::Color
{
public:
    Color(Byte r = 0, Byte g = 0, Byte b = 0, Byte a = 255) { set(r, g, b, a); }

    Byte getA(void) const noexcept { return (_val >> 24) & 0xff; }
    Byte getR(void) const noexcept { return (_val >> 16) & 0xff; }
    Byte getG(void) const noexcept { return (_val >> 8) & 0xff; }
    Byte getB(void) const noexcept { return _val & 0xff; }
    Uint getValue(void) const noexcept { return _val; }

    void set(Byte r, Byte g, Byte b, Byte a = 255) {
        _val = Pack(r, g, b, a);
    }

    void setTransparency(Byte a) {
        _val = Pack(getR(), getG(), getB(), a);
    }

    static Color RetreiveColor(const String &color);

private:
    // Packed color data;
    Uint _val = 0;

    static Uint Pack(Byte r, Byte g, Byte b, Byte a);
};