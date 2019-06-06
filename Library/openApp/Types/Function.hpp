/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Function
*/

#pragma once

// std::function
#include <functional>

namespace oA
{
    /**
     * @brief A simple std::function
     *
     * @tparam Signature Function's signature
     */
    template<typename Signature>
    using Function = std::function<Signature>;
}