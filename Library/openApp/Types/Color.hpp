/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Color
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>

namespace oA { class Color; }

class oA::Color
{
public:
    Color(UByte r = 0, UByte g = 0, UByte b = 0, UByte a = 255) { set(r, g, b, a); }

    UByte getA(void) const noexcept { return (_val >> 24) & 0xff; }
    UByte getR(void) const noexcept { return (_val >> 16) & 0xff; }
    UByte getG(void) const noexcept { return (_val >> 8) & 0xff; }
    UByte getB(void) const noexcept { return _val & 0xff; }
    Uint getValue(void) const noexcept { return _val; }

    void set(UByte r, UByte g, UByte b, UByte a = 255);
    void setTransparency(UByte a);

    static Color RetreiveColor(const String &color);

private:
    // Packed color data;
    Uint _val = 0;

    inline static Uint Pack(UByte r, UByte g, UByte b, UByte a);
};