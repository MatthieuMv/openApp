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
    template<typename Signature>
    using Function = std::function<Signature>;
}