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