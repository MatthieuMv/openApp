/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** List
*/

#pragma once

// std::list
#include <list>

#include <openApp/Containers/ContainerHelper.hpp>

namespace oA
{
    /**
     * @brief A std::list extended by ContainerHelper
     *
     * @tparam Value Contained type
     */
    template<typename Value>
    using List = ContainerHelper<std::list<Value>, Value>;
}