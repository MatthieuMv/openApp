/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Tuple
*/

#pragma once

// std::tuple
#include <tuple>

namespace oA
{
    template<typename... Args>
    using Tuple = std::tuple<Args...>;
}