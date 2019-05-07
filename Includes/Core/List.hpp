/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** List
*/

#pragma once

// std::list
#include <list>

// ContainerHelper
#include "Core/ContainerHelper.hpp"

namespace oA
{
    template<typename T>
    using List = ContainerHelper<std::list<T>, T>;
}