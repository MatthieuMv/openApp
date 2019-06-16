/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Containers/Vector.hpp>
#include <openApp/Core/Expression.hpp>
#include <openApp/Core/Var.hpp>

namespace oA::ItemUtils { class ExpressionHandler; }

/**
 * @brief This class is inherited by Item to add member expression management
 */
class oA::ItemUtils::ExpressionHandler
{
public:
    /**
     * @brief Destroy the ExpressionHandler object
     */
    virtual ~ExpressionHandler(void) = default;

    /**
     * @brief Append a generic expression
     *
     * @param key Expression key name
     * @return Expression<T>& Allow chain operators
     */
    Property<Var> &append(const String &key);

    /**
     * @brief Check existence of a member Expression
     *
     * @param key Expression key name
     * @return true Expression exists
     * @return false Expression doesn't exists
     */
    bool exists(const String &key) const noexcept;

    /**
     * @brief Return a non-const reference to matching Expression
     *
     * @param key Expression name
     * @return Property<Var>& Matching expression
     */
    Property<Var> &get(const String &key);

    /**
     * @brief Return a const reference to matching Expression
     *
     * @param key Expression name
     * @return Property<Var>& Matching expression
     */
    const Property<Var> &get(const String &key) const;

    /**
     * @brief Return a const reference to matching Expression as type T
     *
     * @tparam T Type to retreive
     * @param key Expression name
     * @return const T& Matching expression's value
     */
    template<typename T>
    const T &getAs(const String &key) const {
        return get(key)->get<T>();
    }

    /**
     * @brief Get the ExpressionPtr object matching key
     *
     * @param key Expression key to match
     * @return ExpressionPtr<Var> Result expression
     */
    ExpressionPtr<Var> getExprPtr(const String &key) const noexcept;

protected:
    UMap<String, ExpressionPtr<Var>> _members;
};