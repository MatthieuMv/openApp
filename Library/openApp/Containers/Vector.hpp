/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Vector
*/

#pragma once

// std::vector
#include <vector>

#include <openApp/Containers/ContainerHelper.hpp>

namespace oA
{
    /**
     * @brief A std::vector extended by ContainerHelper
     *
     * @tparam Value Contained type
     */
    template<typename Value>
    using Vector = ContainerHelper<std::vector<Value>, Value>;
}