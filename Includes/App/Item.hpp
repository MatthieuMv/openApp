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
#include "Core/UMap.hpp"
#include "Core/Memory.hpp"
#include "Property.hpp"
#include "Variant.hpp"

namespace oA
{
    class Item;

    using ItemPtr = Shared<Item>;
}

class oA::Item : public oA::VObject
{
public:
    Item(void) {
        append("x") = 0;
        append("y") = 0;
        append("width") = 0;
        append("height") = 0;
    }

    /* Child function */
    Item &addChild(const ItemPtr &child);
    Item &addChild(ItemPtr &&child);
    void removeChild(const String &id);
    Uint childCount(void) const noexcept;

    /* Property */
    Property<Variant> &append(const String &name);
    void remove(const String &name);
    Property<Variant> &operator[](const String &name);
    const Property<Variant> &operator[](const String &name) const;

protected:
    List<ItemPtr> _childs;
    UMap<String, Property<Variant>> _properties;
};