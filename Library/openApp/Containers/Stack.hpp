/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Stack
*/

#pragma once

// std::stack
#include <stack>

namespace oA
{
    /**
     * @brief A std::stack extended by ContainerHelper
     *
     * @tparam Value Contained type
     */
    template<typename Value>
    using Stack = std::stack<Value>;
}