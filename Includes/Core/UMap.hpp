/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** UMap
*/

#pragma once

#include <unordered_map>
#include "Core/Pair.hpp"
#include "Core/ContainerHelper.hpp"

namespace oA
{
    template<typename K, typename T>
    using UMap = ContainerHelper<std::unordered_map<K, T>, Pair<K, T>>;
}