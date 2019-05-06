/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Variant
*/

#pragma once

#include <variant>

#include "Core/Scalar.hpp"
#include "Core/String.hpp"
#include "Item.hpp"

namespace oA
{
    using VType = std::variant<Float, String, ItemPtr>;

    enum VariantType {
        VNumber = 0,
        VString,
        VItem
    };

    class Variant;
}

class oA::Variant
{
public:
    Variant(void);
    template<typename T> Variant(const T &value); // Construct any supported type
    Variant(const Variant &other);
    ~Variant(void) = default;

    // Type identification
    VariantType index(void) const noexcept { return static_cast<VariantType>(_var.index()); }
    bool isSameType(const Variant &other) const noexcept { return index() == other.index(); }

    // Retreive any supported types
    Float &toFloat(void);
    String &toString(void);
    ItemPtr &toItemPtr(void);
    const Float &toFloat(void) const;
    const String &toString(void) const;
    const ItemPtr &toItemPtr(void) const;
    Int toInt(void) const;

    // Retreive type name
    String getTypeName(void) const noexcept;
    String getTypeName(VariantType type) const noexcept;

    // Operators
    template<typename T> Variant &operator=(const T &value);
    operator bool(void);
    bool operator==(const Variant &other) const;
    bool operator!=(const Variant &other) const;
    bool operator<(const Variant &other) const;
    bool operator<=(const Variant &other) const;
    bool operator>(const Variant &other) const;
    bool operator>=(const Variant &other) const;
    Variant operator+(const Variant &other) const;
    Variant &operator+=(const Variant &other);
    Variant &operator++(void);
    Variant operator-(const Variant &other) const;
    Variant &operator-=(const Variant &other);
    Variant &operator--(void);
    Variant operator*(const Variant &other) const;
    Variant &operator*=(const Variant &other);
    Variant operator/(const Variant &other) const;
    Variant &operator/=(const Variant &other);
    Variant operator%(const Variant &other) const;
    Variant &operator%=(const Variant &other);

private:
    VType _var;

    // Assert that 'type' is the equal to variant's type
    void assertType(VariantType type) const;
};