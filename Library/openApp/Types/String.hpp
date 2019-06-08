/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** String
*/

#pragma once

// std::string
#include <string>

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/Function.hpp>
#include <openApp/Containers/ContainerHelper.hpp>

namespace oA { class String; }

/**
 * @brief An extended std::string with ContainerHelper and various helper functions
 */
class oA::String : public ContainerHelper<std::string, char>
{
public:
    /**
     * @brief Construct a new String object
     */
    String(void) : ContainerHelper<std::string, char>() {}

    /**
     * @brief Construct a new String object by copy
     *
     * @param other Variable to copy
     */
    String(const String &other) : ContainerHelper<std::string, char>(other) {}

    /**
     * @brief Construct a new String object by move
     *
     * @param other Variable to move
     */
    String(String &&other) : ContainerHelper<std::string, char>(std::move(other)) {}

    /**
     * @brief Construct a new String object with a std::string by copy
     *
     * @param other Variable to copy
     */
    String(const std::string &other) { *this = other; }

    /**
     * @brief Construct a new String object with a std::string by move
     *
     * @param other Variable to move
     */
    String(std::string &&other) { *this = std::move(other); }

    /**
     * @brief Construct a new String object with a char
     *
     * @param c Char to insert
     */
    String(char c) { push_back(c); }

    /**
     * @brief Construct a new String object with a raw C char pointer
     *
     * @param raw C string to copy
     */
    String(const char * const raw) { *this = raw; }

    /* std::string operators */
    using std::string::operator=;
    using std::string::operator+=;
    using std::string::operator std::basic_string_view<char, std::char_traits<char>>;
    using std::string::operator[];

    /**
     * @brief Return internal string state (true if not empty)
     */
    operator bool(void) const noexcept { return !this->empty(); }

    /**
     * @brief Copy assignement operator
     *
     * @param other Value to copy
     * @return String& Allow chain operators
     */
    String &operator=(const String &other) noexcept;


    /**
     * @brief Move assignement operator
     *
     * @param other Value to move
     * @return String& Allow chain operators
     */
    String &operator=(String &&other) noexcept;


    /**
     * @brief Append operator by copy
     *
     * @param other Value to append
     * @return String& Allow chain operators
     */
    String &operator+=(const String &other) noexcept;

    /**
     * @brief Append operator by move
     *
     * @param other Value to append
     * @return String& Allow chain operators
     */
    String &operator+=(String &&other) noexcept;

    /**
     * @brief Boolean cast
     *
     * @return bool Cast result
     */
    bool toBool(void) const;

    /**
     * @brief Int cast
     *
     * @return Int Cast result
     */
    Int  toInt(void) const;

    /**
     * @brief Uint cast
     *
     * @return Uint Cast result
     */
    Uint toUint(void) const;

    /**
     * @brief Float cast
     *
     * @return Float Cast result
     */
    Float toFloat(void) const;

    /**
     * @brief Double cast
     *
     * @return Double Cast result
     */
    Double toDouble(void) const;

    /**
     * @brief Boolean check
     *
     * @return bool Return if the Boolean cast is possible
     */
    bool isBoolean(void) const noexcept;

    /**
     * @brief Number check
     *
     * @return bool Return if a number cast is possible
     */
    bool isNumber(void) const noexcept;

    /**
     * @brief Unsigned check
     *
     * @return bool Return if a perfect Unsigned cast is possible
     */
    bool isSigned(void) const noexcept;

    /**
     * @brief Unsigned check
     *
     * @return bool Return if a perfect Unsigned cast is possible
     */
    bool isUnsigned(void) const noexcept;

    /**
     * @brief Decimal check
     *
     * @return bool Return if a perfect Decimal cast is possible
     */
    bool isDecimal(void) const noexcept;

    /* String helper API
        replace : will replace each occurence of a given sequence with another
        replaceWith : will replace each occurence of a given sequence with the result of a lambda
    */

    /**
     * @brief Replace each occurence of a given sequence with another
     *
     * @param from To replace sequence
     * @param to To insert sequence
     */
    void replace(const String &from, const String &to);

    /**
     * @brief Replace each occurence of a given sequence with the result of a lambda
     *
     * @param from To replace sequence
     * @param to Lambda function returing a String
     */
    void replaceWith(const String &from, const Function<String(void)> &to);
};

namespace oA
{
    /**
     * @brief Convert T to String, removing decimal useless digits if any
     *
     * @tparam T Type to convert
     * @param value Value to convert
     * @return oA::String Converted result
     */
    template<typename T>
    oA::String ToString(T value) {
        String res = std::to_string(value);
        if (res.find('.') == res.npos)
            return res;
        while (res.length() != 1 && res.back() == '0')
            res.pop_back();
        if (res.back() == '.')
            res.pop_back();
        return res;
    }
}

/**
 * @brief Hash used for STL containers with String
 */
template<>
struct std::hash<oA::String>
{
    /**
     * @brief Return a std::hash<std::string> out of a String
     *
     * @param key String to convert
     * @return std::size_t Hashed string
     */
    std::size_t operator()(const oA::String &key) const
    {
        return std::hash<std::string>()(key);
    }
};