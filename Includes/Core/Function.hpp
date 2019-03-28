/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Function
*/

#pragma once

#include <functional>

namespace oA
{
    template<typename T>
    using Function = std::function<T>;
}