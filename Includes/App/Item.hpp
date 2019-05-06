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

    using ItemPtr = Shared<Item>;
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
    Uint size(void) const noexcept { return _childs.size(); }
    Item &operator[](Uint i);
    Item &operator[](Uint i) const;

protected:
    List<ItemPtr> _childs;
};