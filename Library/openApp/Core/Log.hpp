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

namespace oA
{
    class Log;
}

/**
 * @brief OStream logger with color and quotes features
 *
 * This class is an improved version of the traditional stream logger (cout / cerr)
 * You can instanciate yours and customize it to accept different quoting char / color combinaison
 */
class oA::Log
{
public:
    /**
     * @brief Log default standard outputs (stdout / stderr)
     */
    enum Output {
        Stdout = 0,
        Stderr
    };

    /**
     * @brief Construct a new Log object with a standard output
     *
     * @param out Selected standard output
     * @param color text rendering default color
     * @param quotes Vector of text quotes symbols and colors
     */
    Log(Output out = Stdout,
        const ConsoleColor &color = CSL_WHITE,
        const QuoteVector &quotes = QuoteVector());

    /**
     * @brief Construct a new Log object
     *
     * @param os Internal output stream
     * @param color text rendering default color
     * @param quotes Vector of text quotes symbols and colors
     */
    Log(OStream &os,
        const ConsoleColor &color = CSL_WHITE,
        const QuoteVector &quotes = QuoteVector());

    /**
     * @brief Returns internal enabled state
     *
     * @return true Log will forward output to internal OStream
     * @return false Log will not forward to internal OStream
     */
    bool isEnabled(void) const noexcept;

    /**
     * @brief Set the internal enabled state
     *
     * @param value Enabled state
     */
    void setEnabled(bool value) noexcept;

    /**
     * @brief Call the flush method of internal OStream
     */
    void flush(void) noexcept;

    /**
     * @brief Indicate if Log is using color insertions
     *
     * @return bool Color state
     */
    bool useColor(void) const noexcept;

    /**
     * @brief Generic stream operator definition
     *
     * @tparam T Type to be log
     * @param value Value to be log
     * @return Log& Allow chain operators
     */
    template<typename T>
    Log &operator<<(T value) {
        if (!isEnabled())
            return *this;
        repeat([this, &value] { _os << value; });
        return *this;
    }

private:
    OStream &_os;
    ConsoleColor _color;
    ConsoleColor _quote;
    QuoteVector _quotes;
    Repeat _repeat;
    bool _enabled = true;
    bool _useColor = true;

    /**
     * @brief Format a quoted string into a colored string (if using colors)
     *
     * @param str
     */
    void formatQuotedString(String &str);

    /**
     * @brief Init OStream default color
     */
    void initColor(void) noexcept;

    /**
     * @brief Reset OStream color
     */
    void closeColor(void) noexcept;

    /**
     * @brief Repeats a task based on internal repeat count
     *
     * @param task Function to be repeated
     */
    void repeat(const Function<void(void)> &task) noexcept;
};

namespace oA
{
    extern oA::Log              cout;   // replacement to std::cout
    extern oA::Log              cerr;   // replacement to std::cerr
    extern oA::Endl             endl;   // replacement to std::endl
}

template<>
oA::Log &oA::Log::operator<<(String &value);
template<>
oA::Log &oA::Log::operator<<(const char * const value);
template<>
oA::Log &oA::Log::operator<<(char value);
template<>
oA::Log &oA::Log::operator<<(bool value);
template<>
oA::Log &oA::Log::operator<<(Repeat repeat);
template<>
oA::Log &oA::Log::operator<<(Endl);