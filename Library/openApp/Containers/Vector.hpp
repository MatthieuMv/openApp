/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Vector
*/

#pragma once

#include "ContainerHelper.hpp"

namespace oA
{
    template<typename Value>
    using Vector = ContainerHelper<std::vector<Value>, Value>;
}