/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Map
*/

#pragma once

// std::map
#include <map>

#include <openApp/Containers/Pair.hpp>
#include <openApp/Containers/ContainerHelper.hpp>

namespace oA
{
    /**
     * @brief A std::map extended by ContainerHelper
     *
     * @tparam Key Contained key type
     * @tparam Value Contained value type
     */
    template<typename Key, typename Value>
    using Map = ContainerHelper<std::map<Key, Value>, Pair<Key, Value>>;
}