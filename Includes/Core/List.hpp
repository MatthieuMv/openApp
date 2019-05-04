/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** List
*/

#pragma once

#include <list>
#include "ContainerHelper.hpp"

namespace oA
{
    template<typename T>
    using List = ContainerHelper<std::list<T>, T>;
}