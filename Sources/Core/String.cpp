/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** String
*/

// String
#include "Core/String.hpp"

bool oA::IsString(const oA::String &str)
{
    return str.front() == '"' && str.back() == '"';
}

bool oA::IsNumber(const oA::String &str)
{
    bool dot = false;

    for (auto c : str) {
        if (c == '.' || c == ',') {
            if (dot)
                return false;
            dot = true;
        } else if (c < '0' || c > '9')
            return false;
    }
    return true;
}

bool oA::IsBoolean(const oA::String &str)
{
    return str == "true" || str == "false";
}

bool oA::FromBoolean(const oA::String &str)
{
    return str == "true";
}