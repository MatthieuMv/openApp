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
#include <openApp/Containers/List.hpp>
#include <openApp/Core/Signal.hpp>

namespace oA
{
    class Var;

    class Item;

    /**
     * @brief Type that will be used as Number in Var
     */
    using Number = Float;

    /**
     * @brief Type that will be used as Literal in Var
     */
    using Literal = String;

    /**
     * @brief Type that will be used as Container in Var
     */
    using Container = List<Var>;
}

class oA::Var : public Signal<>
{
    /**
     * @brief Internal Variant type
     */
    using VariantType = Variant<Number, Literal, Container>;

public:
    /**
     * @brief Different internal Variant types
     */
    enum VarType {
        VNumber = 0,
        VLiteral,
        VContainer
    };

    /**
     * @brief Destroy the Var object
     */
    virtual ~Var(void) = default;

    /**
     * @brief Construct a new Var object
     */
    Var(void) : Signal<>(), _var(0.0f) {}

    /**
     * @brief Construct a new Var object by copy
     *
     * @param other Var to copy
     */
    Var(const Var &other) : Signal<>(), _var(other._var) {}

    /**
     * @brief Construct a new Var object by move
     *
     * @param other Var to move
     */
    Var(Var &&other) : Signal<>(), _var(0.0f) { swap(other); }

    /**
     * @brief Construct a new Var object by value move
     *
     * @tparam T Value type
     * @param value Value to move
     */
    template<typename T, std::enable_if_t<!std::is_convertible<T, Var>::value> * = nullptr>
    Var(T &&value) : Signal<>(), _var(std::forward<T>(value)) {}

    /**
     * @brief Return internal index as VarType
     *
     * @return VarType Internal index
     */
    constexpr VarType index(void) const noexcept { return static_cast<VarType>(_var.index()); }

    /**
     * @brief Try to extract const reference to internal type T
     *
     * @tparam T Type to extract
     * @return const T& Extracted value
     */
    template<typename T>
    const T &getAs(void) const {
        try {
            return std::get<T>(_var);
        } catch (...) {
            throw LogicError("Var", "Invalid use of @getAs@ function, internal type is currently @" + getTypeName() + '@');
        }
    }

    /**
     * @brief Get internal type name
     *
     * @return String Type name
     */
    String getTypeName(void) const noexcept;

    /**
     * @brief Swap two Var
     *
     * @param other Value to swap
     */
    void swap(Var &other) noexcept;

    /**
     * @brief Safe cast of internal type to boolean
     */
    bool toBool(void) const noexcept;

    /**
     * @brief Safe cast of internal type to Int
     */
    Int toInt(void) const noexcept;

    /**
     * @brief Safe cast of internal type to Int
     */
    UInt toUInt(void) const noexcept;

    /**
     * @brief Safe cast of internal type to Float
     */
    Float toFloat(void) const noexcept;

    /**
     * @brief Safe cast of internal type to String
     */
    String toString(void) const noexcept;

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
    Var &operator[](const Var &other);
    const Var &operator[](const Var &other) const;

    /* Functions */
    Var len(void) const;
    Var &push(const Var &value);
    Var &push(Var &&value);
    Var &pop(void);
    Var &insert(const Var &index, const Var &value);
    Var &insert(const Var &index, Var &&value);
    Var &remove(const Var &index);

private:
    VariantType _var;
};