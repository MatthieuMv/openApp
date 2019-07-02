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
    /**
     * @brief A simple std::variant
     *
     * @tparam Args Internal types
     */
    template<typename ...Args>
    using Variant = std::variant<Args...>;

    /**
     * @brief C++ Magic Trick to construct lambda-based visitors
     */
    template<typename ...Args> struct Overload : Args... { using Args::operator()...; };

    /**
     * @brief C++ Magic Trick to construct lambda-based visitors
     */
    template<typename ...Args> Overload(Args...) -> Overload<Args...>;
}