/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

#include <iostream>
#include "Core/Log.hpp"

const oA::Log oA::cout(oA::Log::COUT);
const oA::Log oA::cerr(oA::Log::CERR, CSL_LIGHT_YELLOW, CSL_BG_BLACK, CSL_BG_LIGHT_RED);
const oA::Log::Repeater oA::repeat;
const oA::Log::Endl oA::endl;

oA::Log::Log(Output out, ConsoleColor text, ConsoleColor background, ConsoleColor quote)
    : _stream(out == CERR ? std::cerr : std::cout), _text(text), _background(background), _quote(quote)
{
}

oA::OStream &oA::Log::getStream(void) const noexcept
{
    return _stream;
}

oA::Bool oA::Log::repeat(void) const noexcept
{
    return _repeat ? --_repeat, true : false;
}

void oA::Log::setRepeat(oA::Uint value) const noexcept
{
    _repeat = value;
}

oA::Bool oA::Log::getEnabled(void) const noexcept
{
    return _enabled;
}

void oA::Log::setEnabled(oA::Bool value) noexcept
{
    _enabled = value;
}

void oA::Log::formatConsoleString(oA::String &string) const noexcept
{
    oA::Uint pos = string.find('@');
    oA::Uint pos2;

    while (pos != oA::String::npos) {
        pos2 = string.find('@', pos + 1);
        if (pos2 == oA::String::npos)
            break;
        string.replace(string.begin() + pos, string.begin() + pos + 1, _quote);
        string.replace(string.begin() + pos2, string.begin() + pos2 + 1, _text);
        pos = string.find('@', pos2 + 1);
    }
    string.insert(0, _background);
    string.insert(string.length(), CSL_RESET);
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

const oA::Log &operator<<(const oA::Log &log, oA::String string)
{
    log.formatConsoleString(string);
    log.getStream() << string;
    return (log);
}

const oA::Log::Repeater &oA::Log::Repeater::operator()(int x) const noexcept
{
    _x = x;
    return (*this);
}

oA::Uint oA::Log::Repeater::get(void) const noexcept
{
    return _x;
}