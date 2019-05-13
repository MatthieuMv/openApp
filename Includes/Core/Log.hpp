/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

#pragma once

#if !defined(WIN32) && !defined(_WIN32)
    #define CONSOLE_HAS_COLOR
#endif

// Uint
#include "Core/Scalar.hpp"
// String
#include "Core/String.hpp"
// OStream
#include "Core/Stream.hpp"
// ConsoleColor
#include "Core/Console.hpp"
// Variant
#include "Core/Variant.hpp"

#ifndef OA_QUOTE_CHAR
    #define OA_QUOTE_CHAR ('@')
#endif

#ifndef OA_QUOTE_CHAR2
    #define OA_QUOTE_CHAR2 ('#')
#endif

namespace oA { class Log; }

/*
    A Log instance can provide a high level verbose API.
    You can enable / disable it, customize text, quote (OA_QUOTE_CHAR) and background color.
*/
class oA::Log
{
public:
    class Repeater;
    class Endl;

    enum Output {
        COUT = 0,
        CERR
    };

    Log(Output out = COUT,
        ConsoleColor text = ConsoleColor(),
        ConsoleColor quote = ConsoleColor(),
        ConsoleColor quote2 = ConsoleColor());

    OStream &getStream(void) const noexcept;
    bool repeat(void) noexcept;
    void setRepeat(Uint value) noexcept;
    bool getEnabled(void) const noexcept;
    void setEnabled(bool value) noexcept;

    template<typename T>
    Log &log(const T &value) noexcept {
        if (!getEnabled())
            return (*this);
        while (repeat()) {
            getStream() << value;
        }
        _repeat = 1;
        return (*this);
    }

private:
    OStream &_stream;
    Uint _repeat = 1;
    bool _enabled = true;
    ConsoleColor _text;
    ConsoleColor _quote[2];

    void formatConsoleString(String &string) noexcept;
    void formatQuote(String &str, ConsoleColor color, char separator) noexcept;
};

template<>
oA::Log &oA::Log::log(const oA::String &value) noexcept;

class oA::Log::Repeater
{
public:
    Repeater(void) = default;

    Repeater &operator()(Uint x) noexcept;
    Uint get(void) const noexcept;

private:
    Uint _x = 0;
};

class oA::Log::Endl
{
};

template<typename T>
oA::Log &operator<<(oA::Log &log, const T &value) {
    log.log(value);
    return (log);
}

oA::Log &operator<<(oA::Log &log, const oA::Log::Repeater &repeater);
oA::Log &operator<<(oA::Log &log, const oA::Log::Endl &endl);
oA::Log &operator<<(oA::Log &log, const char * const &raw);
oA::Log &operator<<(oA::Log &log, const oA::Variant &var);

namespace oA
{
    extern oA::Log cout;
    extern oA::Log cerr;
    extern oA::Log::Repeater repeat;
    extern oA::Log::Endl endl;
}