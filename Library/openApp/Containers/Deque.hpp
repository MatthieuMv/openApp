/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Deque
*/

#pragma once

// std::deque
#include <deque>

#include <openApp/Containers/ContainerHelper.hpp>

namespace oA
{
    /**
     * @brief A std::deque extended by ContainerHelper
     *
     * @tparam Value Contained type
     */
    template<typename Value>
    using Deque = ContainerHelper<std::deque<Value>, Value>;
}