/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include <openApp/App/ItemHandler.hpp>
#include <openApp/App/PropertyHandler.hpp>
#include <openApp/Render/IRenderer.hpp>
#include <openApp/Render/RenderContexts.hpp>

namespace oA { class Item; }

/**
 * @brief openApp entities' base class
 *
 * Item contains an Expression list, which can be interpreted as member
 * functions or variables. They can be accessed in openApp's design language
 */
class oA::Item : public ItemUtils::ItemHandler, public ItemUtils::PropertyHandler
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
        append("x") = 0; // Parent relative X position
        append("y") = 0; // Parent relative Y position
        append("screenX") = 0; // Screen relative X position
        append("screenY") = 0; // Screen relative Y position
        append("width") = 0; // Item width
        append("height") = 0; // Item height
        append("enabled") = true; // If true, Item will receive and propagate updates
        append("visible") = true; // If true, Item will draw himself and his children
        append("clip") = true; // If true, Item will clip its children on draw
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
    virtual void onAppendChild(Item &child);

    /**
     * @brief Callback on removing child
     *
     * @param child Child to remove
     */
    virtual void onRemoveChild(Item &child);

    /**
     * @brief Callback on internal parent changed
     */
    virtual void onParentChanged(void);

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
     * @param event Received event
     * @return true Don't propagate event
     * @return false Propagate event
     */
    virtual bool onEvent(const Event &) { return false; }

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
     * @brief Get internal parent const pointer
     *
     * @return const Item* Parent pointer
     */
    const Item *getParent(void) const noexcept { return _parent; }

    /**
     * @brief Get root parent pointer
     *
     * @return Item* Root pointer
     */
    Item *getRoot(void) noexcept { return _parent ? _parent->getRoot() : this; }

    /**
     * @brief Get the Area Context object of Item
     *
     * @return AreaContext Item context
     */
    AreaContext getAreaContext(void) const {
        return AreaContext(
            V2f(getAs<Number>("screenX"), getAs<Number>("screenY")),
            V2f(getAs<Number>("width"), getAs<Number>("height"))
        );
    }

    /**
     * @brief Tell if item area contains a point
     *
     * @param point Point data
     * @return true Point is contained in Item
     * @return false Point isn't contained in Item
     */
    template<typename V2 = V2f>
    bool contains(const V2 &point) const {
        Float x = getAs<Number>("screenX"), y = getAs<Number>("screenY");
        return point.x >= x && point.x <= x + getAs<Number>("width")
                && point.y >= y && point.y <= y + getAs<Number>("height");
    }

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
     * @param event Received event
     */
    bool propagate(const Event &event);

    /**
     * @brief Set internal expression of matching key
     *
     * When building an expression, Item makes sure that every dependencies have been set
     *
     * @param target Expression to set
     * @param expression openApp language function as String
     */
    void setExpression(const String &key, const String &expression, const String &context = String());

    /**
     * @brief Set internal expression of matching key
     *
     * When building a function, Item won't add any dependency
     *
     * @param target Expression to set
     * @param expression openApp language function as String
     */
    void setFunction(const String &key, const String &expression, const String &context = String());

    /**
     * @brief Add an event to matching external expression
     *
     * When building an event, Item won't add any dependency
     *
     * @param keyExpr Expression key name (can be relative to external items)
     * @param expression openApp language function as String
     */
    void addExpressionEvent(const String &key, const String &expression, const String &context = String());

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
     * @return PropertyPtr Matching pointer (or null)
     */
    PropertyPtr findExpr(const String &key);

    /**
     * @brief Print to cout item architecture
     *
     * @param tab Tabulation
     */
    void show(Int tab = 0) const noexcept;

private:
    Item *_parent = nullptr; // Must use raw pointer to point parent from inside the class

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