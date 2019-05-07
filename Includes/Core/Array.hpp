/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Array
*/

#pragma once

// std::array
#include <array>

// Uint
#include "Core/Scalar.hpp"

namespace oA
{
    template<typename T, Uint len>
    using Array = std::array<T, len>;
}