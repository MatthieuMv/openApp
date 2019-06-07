/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Stack
*/

#pragma once

// std::stack
#include <stack>

#include <openApp/Containers/Deque.hpp>

namespace oA
{
    /**
     * @brief A simple std::stack
     *
     * @tparam Value Contained type
     * @tparam Container implementation type
     */
    template<typename Value, typename Container = Deque<Value>>
    using Stack = std::stack<Value, Container>;
}