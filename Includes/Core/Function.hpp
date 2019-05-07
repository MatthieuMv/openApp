/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Function
*/

#pragma once

// std::function
#include <functional>

namespace oA
{
    template<typename T>
    using Function = std::function<T>;
}