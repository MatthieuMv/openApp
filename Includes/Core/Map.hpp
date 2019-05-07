/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Map
*/

#pragma once

// std::map
#include <map>

// Pair
#include "Core/Pair.hpp"
// ContainerHelper
#include "Core/ContainerHelper.hpp"

namespace oA
{
    template<typename K, typename T>
    using Map = ContainerHelper<std::map<K, T>, Pair<K, T>>;
}