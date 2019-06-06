/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Array
*/

#pragma once

// std::array
#include <array>

#include <openApp/Types/Scalars.hpp>
#include <openApp/Containers/ContainerHelper.hpp>

namespace oA
{
    /**
     * @brief A std::array extended by ContainerHelper
     *
     * @tparam Value Contained type
     * @tparam Size Array lenght
     */
    template<typename Value, oA::Uint Size>
    using Array = ContainerHelper<std::array<Value, Size>, Value>;
}