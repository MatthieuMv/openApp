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

    template<typename T, typename... Args>
    constexpr inline T &Get(Variant<Args...> &var) { return (std::get<T>(var)); }

    template<typename T, typename... Args>
    constexpr inline const T &Get(const Variant<Args...> &var) { return (std::get<T>(var)); }

    template<typename Visitor, typename... Variants>
    constexpr decltype(auto) Visit(Visitor &&visitor, Variants &&...variants) { return std::visit(std::move(visitor), std::move(variants...)); }

    template<class... Args> struct Overload : Args... { using Args::operator()...; };
    template<class... Args> Overload(Args...) -> Overload<Args...>;
}