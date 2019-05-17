/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Variant
*/

#pragma once

// std::variant
#include <variant>

namespace oA
{
    template<typename ...Args>
    using Variant = std::variant<Args...>;
}