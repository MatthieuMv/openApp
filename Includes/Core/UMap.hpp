/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** UMap
*/

#pragma once

// std::unordered_map
#include <unordered_map>

// Pair
#include "Core/Pair.hpp"
// ContainerHelper
#include "Core/ContainerHelper.hpp"

namespace oA
{
    template<typename K, typename T>
    using UMap = ContainerHelper<std::unordered_map<K, T>, Pair<K, T>>;
}