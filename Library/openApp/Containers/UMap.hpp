/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** UMap
*/

#pragma once

// std::unordered_map
#include <unordered_map>

#include <openApp/Containers/Pair.hpp>
#include <openApp/Containers/ContainerHelper.hpp>

namespace oA
{
    template<typename Key, typename Value>
    using UMap = ContainerHelper<std::unordered_map<Key, Value>, Pair<Key, Value>>;
}