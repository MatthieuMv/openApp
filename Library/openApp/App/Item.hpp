/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include <openApp/App/ItemHandler.hpp>
#include <openApp/App/ExpressionHandler.hpp>
#include <openApp/App/IRenderer.hpp>

namespace oA { class Item; }

/**
 * @brief openApp entities' base class
 *
 * Item contains an Expression list, which can be interpreted as member
 * functions or variables. They can be accessed in openApp's design language
 */
class oA::Item : public ItemUtils::ItemHandler, public ItemUtils::ExpressionHandler
{
public:
    /**
     * @brief Specifies where findItem should search from himself
     */
    enum FindWhere {
        Parents,
        Children,
        Everywhere
    };

    /**
     * @brief Destroy the Item object
     */
    virtual ~Item(void) = default;

    /**
     * @brief Construct a new Item object
     */
    Item(void) {
        append("x") = 0; // X position
        append("y") = 0; // Y position
        append("width") = 0; // Item width
        append("height") = 0; // Item height
        append("enabled") = true; // If true, Item will receive and propagate updates
        append("visible") = true; // If true, Item will draw himself and his children
    }

    /**
     * @brief Can't copy construct an Item
     */
    Item(const Item &) = delete;

    /**
     * @brief Name getter for Item class
     *
     * @return String Name of the class
     */
    virtual String getName(void) const noexcept { return "Item"; }

    /**
     * @brief Callback on appending child
     *
     * @param child New Item
     */
    virtual void onAppendChild(Item &child) { child.setParent(this); }

    /**
     * @brief Callback on removing child
     *
     * @param child Child to remove
     */
    virtual void onRemoveChild(Item &child) { child.setParent(nullptr); }

    /**
     * @brief Callback on internal parent changed
     */
    virtual void onParentChanged(void) {}

    /**
     * @brief Callback on update
     *
     * @param renderer Drawing interface
     */
    virtual void onUpdate(IRenderer &) {}

    /**
     * @brief Callback on draw
     *
     * @param renderer Drawing interface
     */
    virtual void onDraw(IRenderer &) {}

    /**
     * @brief Callback on children drew
     *
     * @param renderer Drawing interface
     */
    virtual void onChildrenDrew(IRenderer &) {}

    /**
     * @brief Called on event handling
     *
     * @param renderer Drawing interface
     * @param event Received event
     * @return true Don't propagate event
     * @return false Propagate event
     */
    virtual bool onEvent(IRenderer &, const Event &) { return false; }

    /**
     * @brief Set internal parent pointer
     *
     * @param parent Parent pointer
     */
    void setParent(Item *parent) { _parent = parent; onParentChanged(); }

    /**
     * @brief Get internal parent pointer
     *
     * @return Item* Parent pointer
     */
    Item *getParent(void) noexcept { return _parent; }

    /**
     * @brief Set internal id
     *
     * @param id ID
     */
    void setID(const String &id) noexcept { _id = id; }

    /**
     * @brief Get internal id
     *
     * @return Item* ID
     */
    const String &getID(void) const noexcept { return _id; }

    /**
     * @brief Update Item and its children
     *
     * @param renderer Drawing interface
     */
    void update(IRenderer &renderer);

    /**
     * @brief Draw Item and its children
     *
     * @param renderer Drawing interface
     */
    void draw(IRenderer &renderer);

    /**
     * @brief Propagate an event though Item and children
     *
     * @param renderer Drawing interface
     * @param event Received event
     */
    bool propagate(IRenderer &renderer, const Event &event);

    /**
     * @brief Set internal expression of matching key
     *
     * When building an expression, Item makes sure that every dependencies have been set
     *
     * @param target Expression to set
     * @param expression openApp language function as String
     */
    void setExpression(const String &key, const String &expression);

    /**
     * @brief Set internal expression of matching key
     *
     * When building a function, Item won't add any dependency
     *
     * @param target Expression to set
     * @param expression openApp language function as String
     */
    void setFunction(const String &key, const String &expression);

    /**
     * @brief Add an event to matching external expression
     *
     * When building an event, Item won't add any dependency
     *
     * @param keyExpr Expression key name (can be relative to external items)
     * @param expression openApp language function as String
     */
    void addExpressionEvent(const String &key, const String &expression);

    /**
     * @brief Find an item using a match key (ex: parent.label)
     *
     * @param key Matching key expression
     * @return ItemPtr Matching pointer (or null)
     */
    Item *findItem(const String &key, FindWhere where = Everywhere);

    /**
     * @brief Find an expression using a match key (ex: parent.label.x)
     *
     * @param key Matching key expression
     * @return ExpressionPtrPtr Matching pointer (or null)
     */
    ExpressionPtr findExpr(const String &key);

    /**
     * @brief Print to cout item architecture
     *
     * @param tab Tabulation
     */
    void show(Int tab = 0) const noexcept;

private:
    Item *_parent = nullptr; // Must use raw pointer to point parent from inside the class
    String _id;

    /**
     * @brief Recursively find an Item in parents
     *
     * @param key Item to find
     * @return Item* Item pointer (can be null)
     */
    Item *findParents(const String &key);

    /**
     * @brief Recursively find an Item in children
     *
     * @param key Item to find
     * @return Item* Item pointer (can be null)
     */
    Item *findChildren(const String &key);
};