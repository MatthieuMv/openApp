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
    virtual ~Item(void) {}

    virtual String getName(void) const noexcept { return "Item"; }

    using OperatorStack = Stack<Operator>;

    /* Child function */
    Item &addChild(const ItemPtr &child);
    Item &addChild(ItemPtr &&child);
    void removeChild(const String &id);
    void removeChild(Uint idx);
    Uint childCount(void) const noexcept;
    Item &getChild(const String &id);
    Item &getChild(Uint idx);
    ItemPtr getChildPtr(const String &id);
    bool childExists(const String &id);

    /* Property */
    Property<Variant> &append(const String &name);
    void remove(const String &name);
    bool exists(const String &name);
    Property<Variant> &get(const String &name);
    const Property<Variant> &get(const String &name) const;
    PropertyPtr<Variant> getPtr(const String &name);
    Property<Variant> &operator[](const String &name);
    const Property<Variant> &operator[](const String &name) const;
    Property<Variant> &operator[](const Char *name);
    const Property<Variant> &operator[](const Char *name) const;

    /* Verbose */
    void show(Uint indent = 0, Log &log = cout) const noexcept;

    /* Find a relative item :
        find() : find an item from parents and childrens
        findProperty() : find an item's property from parent and children
    */
    Item *find(const String &name);
    PropertyPtr<Variant> findProperty(const String &name);

    /* Item Expression */
    Expression<Variant> &getExpr(const String &name);
    const Expression<Variant> &getExpr(const String &name) const;
    void makeExpression(const String &name, const String &targetExpr);

private:
    List<ItemPtr> _childs;
    UMap<String, ExpressionPtr<Variant>> _properties;

    Item *_parent = nullptr;

    /* Find */
    Item *findInParents(const String &name);
    Item *findInChildrens(const String &name);

    /* Item Expression */
    void insertOperator(Expression<Variant> &target, OperatorStack &stack, const String &str);
    void insertOperand(const String &name, Expression<Variant> &target, String &operand);
};

oA::Log &operator<<(oA::Log &log, const oA::Item &item);