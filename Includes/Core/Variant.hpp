/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Variant
*/

#pragma once

// std::variant
#include <variant>

// Float, Int, ...
#include "Core/Scalar.hpp"
// String
#include "Core/String.hpp"

namespace oA
{
    using VType = std::variant<Float, String>;

    enum VariantType {
        VNumber = 0,
        VString
    };

    class Variant;
}

/*
    Variant is a safe static union which handles numbers and litterals
*/
class oA::Variant
{
public:
    // Initialize a Variant
    Variant(void);

    template<typename T>
    Variant(const T &value);

    // Assignment
    Variant &operator=(const Variant &other);

    template<typename T>
    Variant &operator=(const T &value);

    // Type identification
    VariantType index(void) const noexcept { return static_cast<VariantType>(_var.index()); }
    bool isSameType(const Variant &other) const noexcept { return index() == other.index(); }

    // Retreive any supported types without conversion
    template<typename T>
    T &get(void);

    template<typename T>
    const T &getConst(void) const;

    // Safe type conversion getters
    Float toFloat(void) const noexcept;
    Int toInt(void) const noexcept;
    String toString(void) const noexcept;

    // Retreive type name
    String getTypeName(void) const noexcept;
    String getTypeName(VariantType type) const noexcept;

    // Operators
    operator bool(void) const;
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