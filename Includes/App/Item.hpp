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
// Var
#include "App/Var.hpp"
// Log
#include "Core/Log.hpp"
// Context
#include "App/Context.hpp"
// IRenderer
#include "App/IRenderer.hpp"

namespace oA
{
    class Item;

    using ItemPtr = Shared<Item>;
}

class oA::Item
{
public:
    using OperatorStack = Stack<Operator>;

    Item(void) {
        append("id") = "item"; // ID of the Item
        append("x") = 0; // Item parent-relative X
        append("y") = 0; // Item parent-relative Y
        append("width") = 0; // Item width
        append("height") = 0; // Item height
        append("screenX") = 0; // Item screen-relative X
        append("screenY") = 0; // Item screen-relative Y
        append("visible") = true; // Set if the item (and its children) should draw
    }

    virtual ~Item(void) {}

    /* You MUST override this function with the name of your custom class */
    virtual String getName(void) const noexcept { return "Item"; }

    /* Drawing functions :
        render(r) - draw the item and its children
        draw(r) - virtual method drawing only the item to the renderer
    */
    void render(IRenderer &renderer);
    virtual void draw(IRenderer &) {}

    /* Event functions :
        propagate(evt) - propagate an event until an item returns true, starts at the end of item's tree
        onEvent(evt) - virtual method of the item's event handling
    */
    bool propagate(Event &evt);
    virtual bool onEvent(Event &) { return false; }

    /* Items helper */
    bool contains(Float x, Float y) const noexcept;

    /* Item Context */
    void getItemContext(ItemContext &ctx) const;

    /* Verbose */
    void show(Uint indent = 0, Log &log = cout) const noexcept;

    /* Childs function */
    Item &addChild(const ItemPtr &child);
    Item &addChild(ItemPtr &&child);
    Item &setupChild(ItemPtr &child);
    void removeChild(const String &id);
    void removeChild(Uint idx);
    Uint childCount(void) const noexcept;
    Item &getChild(const String &id);
    Item &getChild(Uint idx);
    ItemPtr getChildPtr(const String &id);
    bool childExists(const String &id);

    /* Property */
    Property<Var> &append(const String &name);
    void remove(const String &name);
    bool exists(const String &name);
    Property<Var> &get(const String &name);
    const Property<Var> &get(const String &name) const;
    PropertyPtr<Var> getPtr(const String &name);
    Property<Var> &operator[](const String &name);
    const Property<Var> &operator[](const String &name) const;
    Property<Var> &operator[](const Char *name);
    const Property<Var> &operator[](const Char *name) const;

    /* Item Expression */
    Expression<Var> &getExpr(const String &name);
    const Expression<Var> &getExpr(const String &name) const;
    void makeExpression(const String &name, const String &targetExpr);

    /* Find a relative item :
        find() : find an item from parents and childrens
        findProperty() : find an item's property from parent and children
    */
    Item *find(const String &name);
    PropertyPtr<Var> findProperty(const String &name);

private:
    List<ItemPtr> _childs;
    UMap<String, ExpressionPtr<Var>> _properties;

    Item *_parent = nullptr;

    /* Find */
    Item *findInParents(const String &name);
    Item *findInChildrens(const String &name);

    /* Item Expression */
    void insertOperator(Expression<Var> &target, OperatorStack &stack, const String &str);
    void insertOperand(const String &name, Expression<Var> &target, String &operand);
};

oA::Log &operator<<(oA::Log &log, const oA::Item &item);