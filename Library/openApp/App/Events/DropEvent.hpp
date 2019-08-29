/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** DropEvent
*/

#pragma once

#include <openApp/Types/V2.hpp>
#include <openApp/Types/Memory.hpp>

namespace oA
{
    class Item;

    struct DropEvent;
}

/**
 * @brief Data structure containing a mouse click event
 */
struct oA::DropEvent
{
    Shared<Item> target; // Item droped
    V2i pos; // Data containing drop position (x, y)

    DropEvent(void) = default;
    DropEvent(Shared<Item> &&_target, const V2i _pos) : target(std::move(_target)), pos(_pos) {}
};