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
    /**
     * @brief A std::unordered_map extended by ContainerHelper
     *
     * @tparam Key Contained key type
     * @tparam Value Contained value type
     */
    template<typename Key, typename Value>
    using UMap = ContainerHelper<std::unordered_map<Key, Value>, Pair<Key, Value>>;
}