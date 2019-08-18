/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Pair
*/

#pragma once

#include <utility>

namespace oA
{
    /**
     * @brief A simple std::pair
     *
     * @tparam A First contained type
     * @tparam B Second contained type
     */
    template<typename A, typename B>
    using Pair = std::pair<A, B>;
}