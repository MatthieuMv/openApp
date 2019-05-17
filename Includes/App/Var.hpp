/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Var
*/

#pragma once

// Float, Int, ...
#include "Core/Scalar.hpp"
// String
#include "Core/String.hpp"
// Log
#include "Core/Log.hpp"
// Variant
#include "Core/Variant.hpp"

namespace oA
{
    using VType = Variant<Float, String>;

    enum VarType {
        VNumber = 0,
        VString
    };

    class Var;
}

/*
    Var is a safe static union which handles numbers and litterals
*/
class oA::Var
{
public:
    // Initialize a Var
    Var(void);

    template<typename T>
    Var(const T &value) : _var(value) {}

    // Assignment
    Var &operator=(const Var &other);

    template<typename T>
    Var &operator=(const T &value) {
        _var = value;
        return *this;
    }

    // Type identification
    VarType index(void) const noexcept { return static_cast<VarType>(_var.index()); }
    bool isSameType(const Var &other) const noexcept { return index() == other.index(); }

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
    String getTypeName(VarType type) const noexcept;

    // Operators
    operator bool(void) const;
    bool operator==(const Var &other) const;
    bool operator!=(const Var &other) const;
    bool operator<(const Var &other) const;
    bool operator<=(const Var &other) const;
    bool operator>(const Var &other) const;
    bool operator>=(const Var &other) const;
    Var operator+(const Var &other) const;
    Var &operator+=(const Var &other);
    Var &operator++(void);
    Var operator-(const Var &other) const;
    Var &operator-=(const Var &other);
    Var &operator--(void);
    Var operator*(const Var &other) const;
    Var &operator*=(const Var &other);
    Var operator/(const Var &other) const;
    Var &operator/=(const Var &other);
    Var operator%(const Var &other) const;
    Var &operator%=(const Var &other);

private:
    VType _var;

    // Assert that 'type' is the equal to variant's type
    void assertType(VarType type) const;
};

oA::Log &operator<<(oA::Log &log, const oA::Var &var);