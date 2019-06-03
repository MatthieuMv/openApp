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

namespace oA { class String; }

class oA::String : public std::string
{
public:
    String(void) : std::string() {}
    String(const String &other) : std::string(other) {}
    String(String &&other) : std::string(std::move(other)) {}
    String(const std::string &other) : std::string(other) {}
    String(std::string &&other) : std::string(std::move(other)) {}

    using std::string::string;
    using std::string::operator=;
    using std::string::operator+=;
    using std::string::operator std::basic_string_view<char, std::char_traits<char>>;
    using std::string::operator[];

    bool    toBool(void) const;
    Int     toInt(void) const;
    Uint    toUint(void) const;
    Float   toFloat(void) const;
    Double  toDouble(void) const;

    bool isBoolean(void) const noexcept;
    bool isSigned(void) const noexcept;
    bool isUnsigned(void) const noexcept;
    bool isDecimal(void) const noexcept;
};
