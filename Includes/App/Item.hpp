/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include "Core/Scalar.hpp"
#include "Core/String.hpp"
#include "Core/List.hpp"
#include "Core/Memory.hpp"
#include "Property.hpp"
#include "MakeCode.hpp"

namespace oA
{
    class Item;

    using ItemPtr = Unique<Item>;
}

class oA::Item
{
    MAKE_PROPERTY(String, id)
    MAKE_PROPERTY(Float, x)
    MAKE_PROPERTY(Float, y)
    MAKE_PROPERTY(Float, width)
    MAKE_PROPERTY(Float, height)

public:
    Item(void) = default;

    Item &addChild(ItemPtr &&child);
    void removeChild(const String &id);

protected:
    List<ItemPtr> _childs;
};