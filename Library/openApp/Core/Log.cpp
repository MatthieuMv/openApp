/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

// std::cout, std::cerr, std::endl
#include <iostream>

#include <openApp/Core/Log.hpp>
#include <openApp/Core/Console.hpp>

static const oA::QuoteVector COUT_QUOTES = {
    oA::Quote(oA::CSL_LIGHT_MAGENTA, '#'),
    oA::Quote(oA::CSL_LIGHT_BLUE, '@')
};

static const oA::QuoteVector CERR_QUOTES = {
    oA::Quote(oA::CSL_CYAN, '#'),
    oA::Quote(oA::CSL_LIGHT_RED, '@')
};

/* Global variables */
oA::Log     oA::cout(oA::Log::Stdout, oA::CSL_WHITE, COUT_QUOTES);
oA::Log     oA::cerr(oA::Log::Stdout, oA::CSL_LIGHT_YELLOW, CERR_QUOTES);
oA::Endl    oA::endl;

oA::Log::Log(Output out, const ConsoleColor &color, const QuoteVector &quotes)
    : _os(out == Stdout ? std::cout : std::cerr), _color(color), _quotes(quotes)
{
    _useColor = color != CSL_WHITE || _quotes.size();
}

oA::Log::Log(OStream &os, const ConsoleColor &color, const QuoteVector &quotes)
    : _os(os), _color(color), _quotes(quotes)
{
    _useColor = color != CSL_WHITE || _quotes.size();
}

bool oA::Log::isEnabled(void) const noexcept
{
    return _enabled;
}

void oA::Log::setEnabled(bool value) noexcept
{
    _enabled = value;
}

void oA::Log::flush(void) noexcept
{
    _os.flush();
}

bool oA::Log::useColor(void) const noexcept
{
#ifdef CONSOLE_HAS_COLOR
    return _useColor;
#else
    return false;
#endif
}

void oA::Log::formatQuotedString(String &str)
{
    initColor();
    _quotes.apply([this, &str](const Quote &quote) {
        str.replaceWith(quote.match(), [this, &quote] {
            _quote = _quote == quote.color() ? _color : quote.color();
            return _quote;
        });
    });
}

template<>
oA::Log &oA::Log::operator<<(String value)
{
    if (!isEnabled())
        return *this;
    formatQuotedString(value);
    repeat([this, &value] { _os << value; });
    return *this;
}

template<>
oA::Log &oA::Log::operator<<(const char * const value)
{
    return (*this << oA::String(value));
}


template<>
oA::Log &oA::Log::operator<<(char value)
{
    return (*this << oA::String(value));
}


template<>
oA::Log &oA::Log::operator<<(bool value)
{
    return (*this << oA::String(value ? "true" : "false"));
}


template<>
oA::Log &oA::Log::operator<<(oA::Long value)
{
    return (*this << oA::ToString(value));
}


template<>
oA::Log &oA::Log::operator<<(oA::Double value)
{
    return (*this << oA::ToString(value));
}


template<>
oA::Log &oA::Log::operator<<(Repeat repeat)
{
    if (!isEnabled())
        return *this;
    _repeat = repeat;
    return *this;
}


template<>
oA::Log &oA::Log::operator<<(Endl)
{
    if (!isEnabled())
        return *this;
    closeColor();
    repeat([this]{
        _os << std::endl;
    });
    return *this;
}

bool oA::Log::initColor(void) noexcept
{
    if (!useColor())
        return false;
    if (_quote.empty()) {
        _quote = _color;
        _os << _quote;
    }
    return true;
}

void oA::Log::closeColor(void) noexcept
{
    if (!useColor())
        return;
    _quote.clear();
    _os << oA::CSL_RESET;
}

void oA::Log::repeat(const Function<void(void)> &task) noexcept
{
    auto &count = _repeat.count();

    while (count--)
        task();
    count = 1;
}