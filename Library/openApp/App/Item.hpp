/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include <openApp/App/ItemHandler.hpp>
#include <openApp/App/ExpressionHandler.hpp>

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
     * @brief Construct a new Item object
     */
    Item(void) {
        append("id");
    }

    /**
     * @brief Destroy the Item object
     */
    virtual ~Item(void) = default;

    /**
     * @brief Name getter for Item class
     *
     * @return String Name of the class
     */
    virtual String getName(void) { return "Item"; }

    /**
     * @brief Set internal parent pointer
     *
     * @param parent Parent pointer
     */
    void setParent(Item *parent) { _parent = parent; }

    /**
     * @brief Get internal parent pointer
     *
     * @return Item* Parent pointer
     */
    Item *getParent(Item *parent) { _parent = parent; }

    /**
     * @brief Set new items parent pointer to this
     *
     * @param child Child to set parent
     */
    virtual void onAppendChild(Item &child) { child.setParent(this); }

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
    Item *findItem(const String &key) const noexcept;

    /**
     * @brief Find an expression using a match key (ex: parent.label.x)
     *
     * @param key Matching key expression
     * @return ExpressionPtr<Var>Ptr Matching pointer (or null)
     */
    ExpressionPtr<Var> findExpr(const String &key) const noexcept;

private:
    Item *_parent = nullptr; // Must use raw pointer to point parent from inside the class

    /**
     * @brief Recursively find an Item in parents
     *
     * @param key Item to find
     * @return Item* Item pointer (can be null)
     */
    Item *findInParents(const String &key);

    /**
     * @brief Recursively find an Item in children
     *
     * @param key Item to find
     * @return Item* Item pointer (can be null)
     */
    Item *findInChildren(const String &key);

    /**
     * @brief Set target internal expression
     *
     * @param target Expression to set
     * @param expression openApp language function as String
     * @param addDependency Add dependencies on each parameters of the expression
     */
    void setExpression(Expression<Var> &target, String expression, bool addDependency);

    /**
     * @brief Slit an expression key into two string
     *
     * @param expr Input expression
     * @param token String to fill with right part
     * @return String Name of the first variable
     */
    static String SplitKeyExpr(const String &expr, String &token);
};