/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Queue
*/

#pragma once

// std::queue
#include <queue>

#include <openApp/Containers/Deque.hpp>

namespace oA
{
    /**
     * @brief A simple std::queue
     *
     * @tparam Value Contained type
     * @tparam Container implementation type
     */
    template<typename Value, typename Container = Deque<Value>>
    using Queue = std::queue<Value, Container>;
}