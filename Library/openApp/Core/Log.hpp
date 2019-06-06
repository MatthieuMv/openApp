/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

#pragma once

#include <openApp/Types/String.hpp>
#include <openApp/Types/Stream.hpp>
#include <openApp/Core/LogUtils.hpp>
#include <openApp/Containers/Stack.hpp>

namespace oA { class Log; }

/* Log
    This class is an improved version of the traditional stream logger (cout / cerr)
    You can customize it to accept different quoting char / color combinaison
*/
class oA::Log
{
public:
    enum Output {
        Stdout = 0,
        Stderr
    };

    Log(Output out = Stdout,
        const ConsoleColor &color = CSL_WHITE,
        const QuoteVector &quotes = QuoteVector());

    Log(OStream &os,
        const ConsoleColor &color = CSL_WHITE,
        const QuoteVector &quotes = QuoteVector());

    bool isEnabled(void) const noexcept;
    void setEnabled(bool value) noexcept;

    void flush(void) noexcept;

    bool useColor(void) const noexcept;

    template<typename T>
    Log &operator<<(T value);

    void formatQuotedString(String &str);

private:
    OStream &_os;
    ConsoleColor _color;
    ConsoleColor _quote;
    QuoteVector _quotes;
    Repeat _repeat;
    bool _enabled = true;
    bool _useColor = true;

    bool initColor(void) noexcept;
    void closeColor(void) noexcept;

    void repeat(const Function<void(void)> &task) noexcept;
};

namespace oA
{
    extern oA::Log              cout;   // replacement to std::cout
    extern oA::Log              cerr;   // replacement to std::cerr
    extern oA::Endl             endl;   // replacement to std::endl
}

template<>
oA::Log &oA::Log::operator<<(String value);
template<>
oA::Log &oA::Log::operator<<(const char * const value);
template<>
oA::Log &oA::Log::operator<<(char value);
template<>
oA::Log &oA::Log::operator<<(bool value);
template<>
oA::Log &oA::Log::operator<<(oA::Long value);
template<>
oA::Log &oA::Log::operator<<(oA::Double value);
template<>
oA::Log &oA::Log::operator<<(Repeat repeat);
template<>
oA::Log &oA::Log::operator<<(Endl);