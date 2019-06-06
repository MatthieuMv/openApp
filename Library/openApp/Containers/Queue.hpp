/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Queue
*/

#pragma once

// std::queue
#include <queue>

namespace oA
{
    /**
     * @brief A std::queue extended by ContainerHelper
     *
     * @tparam Value Contained type
     */
    template<typename Value>
    using Queue = std::queue<Value>;
}