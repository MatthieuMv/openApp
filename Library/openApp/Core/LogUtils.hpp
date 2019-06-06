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

/**
 * @brief Quote contains a matching symbol and a color
 *
 * This class is used to initialize a #Log
 */
class oA::Quote
{
public:
    /**
     * @brief Construct a new Quote object using a color and a symbol
     *
     * @param color Matching color
     * @param match Matching character
     */
    Quote(const ConsoleColor &color, char match) : _color(color), _match(match) {}

    /**
     * @brief Return matching symbol
     *
     * @return char Matching symbol
     */
    char match(void) const noexcept { return _match; }

    /**
     * @brief Return internal color
     *
     * @return const ConsoleColor& Internal color
     */
    const ConsoleColor &color(void) const noexcept { return _color; }

private:
    ConsoleColor _color;
    char _match;
};


/**
 * @brief Repeat is used to repeat a #Log stream operation
 */
class oA::Repeat
{
public:
    /**
     * @brief Construct a new Repeat object
     *
     * @param times Stream count
     */
    Repeat(Uint times) : _count(times) {}

private:
    Uint _count = 1;
};

/**
 * @brief Endl is used to insert a newline and flush into a #Log
 */
class oA::Endl
{
};