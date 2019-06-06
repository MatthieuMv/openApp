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
    template<typename Value, oA::Uint size>
    using Array = ContainerHelper<std::array<Value, size>, Value>;
}