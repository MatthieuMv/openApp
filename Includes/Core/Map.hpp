/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Map
*/

#pragma once

#include <map>
#include "Core/Pair.hpp"
#include "Core/ContainerHelper.hpp"

namespace oA
{
    template<typename K, typename T>
    using Map = ContainerHelper<std::map<K, T>, Pair<K, T>>;
}