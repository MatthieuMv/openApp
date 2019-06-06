/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** LogUtils
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Containers/Vector.hpp>
#include <openApp/Core/Console.hpp>

namespace oA
{
    class Quote;
    class Repeat;
    class Endl;

    using QuoteVector = Vector<Quote>;
}

class oA::Quote
{
public:
    Quote(const ConsoleColor &color, char match) : _color(color), _match(match) {}

    char match(void) const noexcept { return _match; }
    const ConsoleColor &color(void) const noexcept { return _color; }

private:
    ConsoleColor _color;
    char _match;
};


class oA::Repeat
{
public:
    Repeat(void) = default;
    Repeat(Uint times) : _count(times) {}
    Uint &count(void) noexcept { return (_count); }

private:
    Uint _count = 1;
};

class oA::Endl
{
};