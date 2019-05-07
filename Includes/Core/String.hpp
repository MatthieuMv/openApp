/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** String
*/

#pragma once

// std::string
#include <string>

namespace oA
{
    using String = std::string;

    template<typename T>
    String ToString(const T &value) {
        auto res = std::to_string(value);
        while (res.back() == '0' || res.back() == '.')
            res.pop_back();
        return res;
    }
}