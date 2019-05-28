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

    template<typename Visitor, typename... Variants>
    constexpr decltype(auto)
    Visit(Visitor &&visitor, Variants &&...variants) { return std::visit(std::move(visitor), std::move(variants...)); }

    template<class... Args> struct Overload : Args... { using Args::operator()...; };
    template<class... Args> Overload(Args...) -> Overload<Args...>;
}