/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Tuple
*/

#pragma once

#include <tuple>

namespace oA
{
    /**
     * @brief A std::list extended by ContainerHelper
     *
     * @tparam Args Contained types
     */
    template<typename... Args>
    using Tuple = std::tuple<Args...>;
}