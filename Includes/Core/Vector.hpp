/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Vector
*/

#pragma once

// std::vector
#include <vector>

// ContainerHelper
#include "ContainerHelper.hpp"

namespace oA
{
    template<typename T>
    using Vector = ContainerHelper<std::vector<T>, T>;
}