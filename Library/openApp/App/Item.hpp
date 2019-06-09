/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include <openApp/Core/Expression.hpp>
#include <openApp/App/Var.hpp>

namespace oA { class Item; }

/**
 * @brief openApp entities' base class
 *
 * Item contains an Expression list, which can be interpreted as member
 * functions or variables. They can be accessed in openApp's design language
 */
class oA::Item
{
public:
    // /**
    //  * @brief Construct a new Item object
    //  */
    // Item(void) {
    //     append("id");
    // }

    // /**
    //  * @brief Destroy the Item object
    //  */
    // virtual ~Item(void) = default;

    // /**
    //  * @brief Name getter for Item class
    //  *
    //  * @return String Name of the class
    //  */
    // virtual String getName(void) { return "Item"; }

    // /**
    //  * @brief Append a generic expression
    //  *
    //  * @param key Expression key name
    //  * @return Expression<T>& Allow chain operators
    //  */
    // Property<Var> &append(const String &key);

    // /**
    //  * @brief Check existence of a member Expression
    //  *
    //  * @param key Expression key name
    //  * @return true Expression exists
    //  * @return false Expression doesn't exists
    //  */
    // bool exists(const String &key);

    // /**
    //  * @brief Return a non-const reference to matching Expression
    //  *
    //  * @param key Expression name
    //  * @return Property<Var>& Matching expression
    //  */
    // Property<Var> &get(const String &key);

    // /**
    //  * @brief Return a const reference to matching Expression
    //  *
    //  * @param key Expression name
    //  * @return Property<Var>& Matching expression
    //  */
    // const Property<Var> &get(const String &key) const;

    // /**
    //  * @brief Set internal expression matching key, create one if none has been found
    //  *
    //  * When building an expression, Item makes sure that every dependencies have been set
    //  *
    //  * @param key Expression key name
    //  * @param expression openApp language expression as String
    //  */
    // void setExpression(const String &key, String expression);

    // /**
    //  * @brief Add an event to matching internal expression
    //  *
    //  * When building an event, Item won't add any dependency
    //  *
    //  * @param key Expression key name
    //  * @param expression openApp language function as String
    //  */
    // void addExpressionEvent(const String &key, String event);

    // /**
    //  * @brief Add a child ItemPtr by move
    //  *
    //  * @param child Value to move
    //  */
    // void appendChild(ItemPtr &&child);

    // /**
    //  * @brief Check existence of a child (using internal id)
    //  *
    //  * @param id Child id to find
    //  * @return true Child has been found
    //  * @return false Child hasn't been found
    //  */
    // bool existsChild(const String &id);

    // /**
    //  * @brief Return a non-const reference to matching child (using internal id)
    //  *
    //  * @param id Child id to find
    //  * @return Item& Matching child
    //  */
    // Item &getChild(const String &id);

    // /**
    //  * @brief Return a const reference to matching child (using internal id)
    //  *
    //  * @param id Child id to find
    //  * @return Item& Matching child
    //  */
    // const Item &getChild(const String &id) const;

private:
    UMap<String, ExpressionPtr<Var>> _members;
    List<ItemPtr> _childs;
};