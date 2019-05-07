/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

// List
#include "Core/List.hpp"
// UMap
#include "Core/UMap.hpp"
// Shared
#include "Core/Memory.hpp"
// Property
#include "Core/Property.hpp"
// Variant
#include "Core/Variant.hpp"

namespace oA
{
    class Item;

    using ItemPtr = Shared<Item>;
}

class oA::Item
{
public:
    Item(void) {
        append("id") = "item";
        append("x") = 0;
        append("y") = 0;
        append("width") = 0;
        append("height") = 0;
    }

    /* Child function */
    Item &addChild(const ItemPtr &child);
    Item &addChild(ItemPtr &&child);
    void removeChild(const String &id);
    void removeChild(Uint idx);
    Uint childCount(void) const noexcept;

    /* Property */
    Property<Variant> &append(const String &name);
    void remove(const String &name);
    Property<Variant> &get(const String &name);
    const Property<Variant> &get(const String &name) const;
    Property<Variant> &operator[](const String &name);
    const Property<Variant> &operator[](const String &name) const;
    Property<Variant> &operator[](const char *name);
    const Property<Variant> &operator[](const char *name) const;

protected:
    List<ItemPtr> _childs;
    UMap<String, Property<Variant>> _properties;
};