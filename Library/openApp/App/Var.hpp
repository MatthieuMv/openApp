/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Var
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/Variant.hpp>
#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Containers/Vector.hpp>

namespace oA
{
    class Var;

    class Item;

    /**
     * @brief Shared pointer to Item
     */
    using ItemPtr = Shared<Item>;
}

class oA::Var
{
public:
    /**
     * @brief Different internal Variant types
     */
    enum VarType {
        VNumber = 0,
        VLiteral,
        VItem,
        VContainer
    };

    /**
     * @brief Type that will be used as Number
     */
    using Number = Float;

    /**
     * @brief Type that will be used as Literal
     */
    using Literal = String;

    /**
     * @brief Type that will be used as Number
     */
    using Container = Vector<Var>;

    /**
     * @brief Internal Variant type
     */
    using VariantType = Variant<Number, Literal, ItemPtr, Container>;

    /**
     * @brief Construct a new Var object
     */
    Var(void) : _var(0.0f) {}

    /**
     * @brief Construct a new Var object by copy
     *
     * @param other Var to copy
     */
    Var(const Var &other) : _var(other._var) {}

    /**
     * @brief Construct a new Var object by move
     *
     * @param other Var to move
     */
    Var(Var &&other) : _var(std::move(other._var)) {}

    /**
     * @brief Construct a new Var object by value copy
     *
     * @tparam T Value type
     * @param value Value to copy
     */
    template<typename T>
    Var(const T &value) : _var(value) {}

    /**
     * @brief Copy assignment
     *
     * @param other Var to copy
     * @return Var& Allow chain operators
     */
    Var &operator=(const Var &other);

    /**
     * @brief Move assignment
     *
     * @param other Var to move
     * @return Var& Allow chain operators
     */
    Var &operator=(Var &&other);

    /**
     * @brief Return internal index as VarType
     *
     * @return VarType Internal index
     */
    VarType index(void) const noexcept { return static_cast<VarType>(_var.index()); }

    /**
     * @brief Try to extract non-const reference to internal type T
     *
     * @tparam T Type to extract
     * @return T& Extracted value
     */
    template<typename T>
    constexpr T &get(void) { return std::get<T>(_var); }

    /**
     * @brief Try to extract const reference to internal type T
     *
     * @tparam T Type to extract
     * @return const T& Extracted value
     */
    template<typename T>
    constexpr const T &get(void) const { return std::get<T>(_var); }

    /**
     * @brief Safe cast of internal type to boolean
     */
    bool toBool(void) const noexcept;

    /**
     * @brief Safe cast of internal type to Int
     */
    Int toInt(void) const noexcept;

    /**
     * @brief Safe cast of internal type to Float
     */
    Float toFloat(void) const noexcept;

    /**
     * @brief Safe cast of internal type to String
     */
    String toString(void) const noexcept;

    /* Boolean operators */
    operator bool(void) const noexcept;
    bool operator!(void) const noexcept;
    bool operator==(const Var &other) const;
    bool operator!=(const Var &other) const;
    bool operator<(const Var &other) const;
    bool operator<=(const Var &other) const;
    bool operator>(const Var &other) const;
    bool operator>=(const Var &other) const;

    /* Read only operators */
    Var operator+(const Var &other) const;
    Var operator-(const Var &other) const;
    Var operator*(const Var &other) const;
    Var operator/(const Var &other) const;
    Var operator%(const Var &other) const;

    /* Assign operators */
    Var &operator+=(const Var &other);
    Var &operator-=(const Var &other);
    Var &operator*=(const Var &other);
    Var &operator/=(const Var &other);
    Var &operator%=(const Var &other);

    /* Increment / Decrement operators */
    Var &operator++(void);
    Var &operator--(void);
    Var operator++(Int);
    Var operator--(Int);

    /* Access operators */
    Var &operator[](Uint idx);

    /* Special functions */

private:
    VariantType _var;
};