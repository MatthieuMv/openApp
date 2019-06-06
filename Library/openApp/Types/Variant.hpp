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
     * @brief Non-const getter for Variant
     *
     * @tparam T Asked type
     * @tparam Args Variant internal types
     * @param var Value to exctract
     * @return constexpr T& Result
     */
    template<typename T, typename... Args>
    constexpr inline T &Get(Variant<Args...> &var) { return (std::get<T>(var)); }

    /**
     * @brief Const getter for Variant
     *
     * @tparam T Asked type
     * @tparam Args Variant internal types
     * @param var Value to extract
     * @return constexpr T& Result
     */
    template<typename T, typename... Args>
    constexpr inline const T &Get(const Variant<Args...> &var) { return (std::get<T>(var)); }

    /**
     * @brief A simple std::visit wrapper
     *
     * @tparam Visitor Visitor type
     * @tparam Variants Variant inernal types
     * @param visitor Visition instance
     * @param variants Values to extract
     * @return auto Result
     */
    template<typename Visitor, typename... Variants>
    constexpr decltype(auto) Visit(Visitor &&visitor, Variants &&...variants) { return std::visit(std::move(visitor), std::move(variants...)); }

    /**
     * @brief C++ Magic Trick to construct lambda-based visitors
     */
    template<class... Args> struct Overload : Args... { using Args::operator()...; };

    /**
     * @brief C++ Magic Trick to construct lambda-based visitors
     */
    template<class... Args> Overload(Args...) -> Overload<Args...>;
}