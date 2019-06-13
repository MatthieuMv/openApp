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
// V2
#include "Core/V2.hpp"

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
        auto &v = append("visible") = true; // Condition for an item (and children) to be updated and draw
        v.connect([this] { get(*get("visible") ? "show" : "hide").emit(); return true; });
        append("show");
        append("hide");
    }

    virtual ~Item(void) {}

    /* You MUST override this function with the name of your custom class */
    virtual String getName(void) const noexcept { return "Item"; }

    /* Render functions :
        render(r) - draw the item and its children
        update(renderer) - custom update function
        draw(r) - virtual method drawing only the item to the renderer
    */
    void render(IRenderer &renderer);
    virtual void draw(IRenderer &) {}
    virtual void update(IRenderer &) {}

    /* Event functions :
        propagate(evt) - propagate an event until an item returns true, starts at the end of item's tree
        onEvent(evt) - virtual method of the item's event handling
    */
    bool propagate(Event &evt);
    virtual bool onEvent(Event &) { return false; }

    /* Items geometry helper */
    bool contains(const V2f &pos) const noexcept;

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

    /* Childs events */
    virtual void onChildAdded(void) {}
    virtual void onChildRemoved(void) {}

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
    ExpressionPtr<Var> getExprPtr(const String &name);
    void makeExpression(const String &name, const String &targetExpr);
    void addExpressionEvent(const oA::String &name, const oA::String &targetExpr);

    /* Find a relative item :
        find() : find an item from parents and childrens
        findExpression() : find an item's expression from parent and children
    */
    Item *find(const String &name);
    ExpressionPtr<Var> findExpression(const String &name);

protected:
    List<ItemPtr> _childs;
    UMap<String, ExpressionPtr<Var>> _properties;

    Item *_parent = nullptr;

    /* Find */
    Item *findInParents(const String &name);
    Item *findInChildrens(const String &name);

private:
    /* Item Expression */
    void makeExpression(Expression<Var> &target, const String &targetExpr, bool hasDependencies, bool compute);
    void insertOperator(Expression<Var> &target, OperatorStack &stack, const String &str);
    void insertOperand(Expression<Var> &target, String &operand, bool hasDependencies);
};

oA::Log &operator<<(oA::Log &log, const oA::Item &item);