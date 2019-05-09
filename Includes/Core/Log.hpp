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
#include "Scalar.hpp"
// String
#include "String.hpp"
// OStream
#include "Stream.hpp"
// ConsoleColor
#include "Console.hpp"

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
    bool repeat(void) const noexcept;
    void setRepeat(Uint value) const noexcept;
    bool getEnabled(void) const noexcept;
    void setEnabled(bool value) noexcept;

    template<typename T>
    const Log &log(const T &value) const noexcept {
        if (!getEnabled())
            return (*this);
        do {
            getStream() << value;
        } while (repeat());
        return (*this);
    }

private:
    OStream &_stream;
    mutable Uint _repeat = 0;
    bool _enabled = true;
    ConsoleColor _text;
    ConsoleColor _quote[2];
    mutable bool _inQuote[2] = { false, false };

    void formatConsoleString(String &string) const noexcept;
    void formatQuote(String &str, bool &inQuote, ConsoleColor color, char separator) const noexcept;
};

template<>
const oA::Log &oA::Log::log(const oA::String &value) const noexcept;

class oA::Log::Repeater
{
public:
    Repeater(void) = default;

    const Repeater &operator()(int x) const noexcept;
    Uint get(void) const noexcept;

private:
    mutable Uint _x = 0;
};

class oA::Log::Endl
{
};

template<typename T>
const oA::Log &operator<<(const oA::Log &log, const T &value) {
    log.log(value);
    return (log);
}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Repeater &repeater);
const oA::Log &operator<<(const oA::Log &log, const oA::Log::Endl &endl);
const oA::Log &operator<<(const oA::Log &log, const char * const &raw);

namespace oA
{
    extern const oA::Log cout;
    extern const oA::Log cerr;
    extern const oA::Log::Repeater repeat;
    extern const oA::Log::Endl endl;
}