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
// Expression, Property
#include "Core/Expression.hpp"
// Variant
#include "Core/Variant.hpp"
// Log
#include "Core/Log.hpp"

namespace oA
{
    class Item;

    using ItemPtr = Shared<Item>;
    using ItemRef = Weak<Item>;
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

    virtual String getName(void) const noexcept { return "Item"; }

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

    /* Verbose */
    void show(Uint indent = 0) const noexcept;
    void showWith(Uint indent, Log &log) const noexcept;

protected:
    List<ItemPtr> _childs;
    UMap<String, ExpressionPtr<Variant>> _properties;
};

oA::Log &operator<<(oA::Log &log, const oA::Item &item);