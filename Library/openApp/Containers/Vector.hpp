/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Vector
*/

#pragma once

#include <openApp/Containers/ContainerHelper.hpp>

namespace oA
{
    template<typename Value>
    using Vector = ContainerHelper<std::vector<Value>, Value>;
}