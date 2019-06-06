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
    template<typename Value>
    using Deque = ContainerHelper<std::deque<Value>, Value>;
}