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

class oA::String : public ContainerHelper<std::string, char>
{
    using Helper = ContainerHelper<std::string, char>;

public:
    String(void) : Helper() {}
    String(const String &other) : Helper(other) {}
    String(String &&other) : Helper(std::move(other)) {}
    String(const std::string &other) { *this = other; }
    String(std::string &&other) { *this = std::move(other); }
    String(char c) { push_back(c); }
    String(const char * const raw) { *this = raw; }

    /* std::string operators */
    using std::string::operator=;
    using std::string::operator+=;
    using std::string::operator std::basic_string_view<char, std::char_traits<char>>;
    using std::string::operator[];

    /* String operators */
    operator bool(void) const noexcept { return !this->empty(); }
    String &operator=(const String &other) noexcept;
    String &operator=(String &&other) noexcept;
    String &operator+=(const String &other) noexcept;
    String &operator+=(String &&other) noexcept;

    /* String cast :
        toXYZ : convert current string to XYZ (throw on cast error)
        isXYZ : return true if the string can be converted into XYZ
    */
    bool    toBool(void) const;
    Int     toInt(void) const;
    Uint    toUint(void) const;
    Float   toFloat(void) const;
    Double  toDouble(void) const;
    bool    isBoolean(void) const noexcept;
    bool    isSigned(void) const noexcept;
    bool    isUnsigned(void) const noexcept;
    bool    isDecimal(void) const noexcept;

    /* String helper API
        replace : will replace each occurence of a given sequence with another
        replaceWith : will replace each occurence of a given sequence with the result of a lambda
    */
    void replace(const String &from, const String &to);
    void replaceWith(const String &from, const Function<String(void)> &to);
};

namespace oA
{
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

/* Hash used for STL containers */
template <>
struct std::hash<oA::String>
{
    std::size_t operator()(const oA::String &key) const
    {
        return std::hash<std::string>()(key);
    }
};