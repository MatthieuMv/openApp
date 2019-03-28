/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Map
*/

#pragma once

#include <map>

namespace oA
{
    template<typename K, typename T>
    using Map = std::map<K, T>;
}