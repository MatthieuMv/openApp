/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** UMap
*/

#pragma once

#include <unordered_map>

namespace oA
{
    template<typename K, typename T>
    using UMap = std::unordered_map<K, T>;
}