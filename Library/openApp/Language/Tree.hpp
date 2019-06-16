/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Tree
*/

#pragma once

#include <openApp/Containers/Vector.hpp>

namespace oA { template<typename T> struct Tree; }

/**
 * @brief Node of an Abstract Syntax Tree
 *
 * @tparam T Type of the node
 */
template<typename T>
struct oA::Tree
{
    Vector<Tree<T>> childs;
    T value;
};