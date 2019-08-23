/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Property
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Containers/Vector.hpp>
#include <openApp/Core/Property.hpp>
#include <openApp/Core/Var.hpp>

namespace oA::ItemUtils { class PropertyHandler; }

/**
 * @brief This class is inherited by Item to add member expression management
 */
class oA::ItemUtils::PropertyHandler
{
public:
    /**
     * @brief Destroy the PropertyHandler object
     */
    virtual ~PropertyHandler(void) = default;

    /**
     * @brief Append a generic expression
     *
     * @param key Property key name
     * @return Property& Allow chain operators
     */
    Var &append(const String &key);

    /**
     * @brief Check existence of a member Property
     *
     * @param key Property key name
     * @return true Property exists
     * @return false Property doesn't exists
     */
    bool exists(const String &key) const noexcept;

    /**
     * @brief Return a non-const reference to matching Property
     *
     * @param key Property name
     * @return Property& Matching expression
     */
    Var &get(const String &key);

    /**
     * @brief Return a const reference to matching Property
     *
     * @param key Property name
     * @return Property& Matching expression
     */
    const Var &get(const String &key) const;

    /**
     * @brief Return a const reference to matching Property as type T
     *
     * @tparam T Type to retreive
     * @param key Property name
     * @return const T& Matching expression's value
     */
    template<typename T>
    const T &getAs(const String &key) const {
        try {
            return get(key).getAs<T>();
        } catch (const LogicError &e) {
            throw LogicError(e.what() + String("\n\t-> from '#") + getID() + "#': @" + key + '@');
        }
    }

    /**
     * @brief Get the PropertyPtr object matching key
     *
     * @param key Property key to match
     * @return PropertyPtr Result expression
     */
    PropertyPtr getPtr(const String &key) const noexcept;

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

protected:
    UMap<String, PropertyPtr> _members;
    String _id;
};