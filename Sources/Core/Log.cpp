/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

// std::cout, std::cerr
#include <iostream>

// Log
#include "Core/Log.hpp"

const oA::Log oA::cout(oA::Log::COUT, oA::CSL_WHITE, oA::CSL_LIGHT_BLUE, oA::CSL_LIGHT_MAGENTA);
const oA::Log oA::cerr(oA::Log::CERR, oA::CSL_LIGHT_YELLOW, oA::CSL_LIGHT_RED, oA::CSL_CYAN);
const oA::Log::Repeater oA::repeat;
const oA::Log::Endl oA::endl;

oA::Log::Log(Output out, ConsoleColor text, ConsoleColor quote, ConsoleColor quote2)
    : _stream(out == CERR ? std::cerr : std::cout), _text(text), _quote({quote, quote2})
{
    if (_text.empty())
        _text = oA::CSL_WHITE;
    for (auto &q : _quote) {
        if (q.empty())
            q = oA::CSL_LIGHT_BLUE;
    }
}

oA::OStream &oA::Log::getStream(void) const noexcept
{
    return _stream;
}

bool oA::Log::repeat(void) const noexcept
{
    return _repeat ? --_repeat, true : false;
}

void oA::Log::setRepeat(oA::Uint value) const noexcept
{
    _repeat = value;
}

bool oA::Log::getEnabled(void) const noexcept
{
    return _enabled;
}

void oA::Log::setEnabled(bool value) noexcept
{
    _enabled = value;
}

void oA::Log::formatConsoleString(String &str) const noexcept
{
    formatQuote(str, _inQuote[0], _quote[0], OA_QUOTE_CHAR);
    formatQuote(str, _inQuote[1], _quote[1], OA_QUOTE_CHAR2);
}

void oA::Log::formatQuote(String &str, bool &inQuote, ConsoleColor quote, char separator) const noexcept
{
    bool hasColor = false;
    auto end = String::npos;
    ConsoleColor color;

#ifdef CONSOLE_HAS_COLOR
    hasColor = true;
#endif
    for (auto pos = str.find(separator); pos != end; pos = str.find(separator, pos + 1)) {
        inQuote = !inQuote;
        if (hasColor)
            color = inQuote ? quote : CSL_RESET + _text;
        else
            color = '\'';
        str.replace(str.begin() + pos, str.begin() + pos + 1, color);
    }
    if (hasColor) {
        str.insert(0, _text);
        str.insert(str.length(), CSL_RESET);
    }
}

template<>
const oA::Log &oA::Log::log(const String &value) const noexcept
{
    String str = value;

    formatConsoleString(str);
    if (!getEnabled())
        return (*this);
    do {
        getStream() << str;
    } while (repeat());
    return (*this);
}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Repeater &repeater)
{
    log.setRepeat(repeater.get());
    return (log);
}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Endl &endl)
{
    (void)(endl);
    if (!log.getEnabled())
        return (log);
    log.getStream() << std::endl;
    return (log);
}

const oA::Log &operator<<(const oA::Log &log, const char * const &raw)
{
    log.log(oA::String(raw));
    return (log);
}

const oA::Log::Repeater &oA::Log::Repeater::operator()(Int x) const noexcept
{
    _x = x;
    return (*this);
}

oA::Uint oA::Log::Repeater::get(void) const noexcept
{
    return _x;
}