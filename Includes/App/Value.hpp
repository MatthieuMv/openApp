/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Value
*/

#pragma once

#include "Variant.hpp"

namespace oA
{
    template<typename T> class Value;

    enum ValueType {
        INT = 0,
        FLOAT,
        STRING,
        NONE_VALUE
    };

    ValueType GetValueType(const String &name) {
        return  name == "Int" ? INT :
                name == "Float" ? FLOAT :
                name == "String" ? STRING :
                NONE_VALUE;
    }
}

template<typename T>
class oA::Value : public oA::Variant
{
public:
    Value(const T &value = T()) : _value(value) {}
    virtual ~Value(void) = default;

    const T &get(void) const noexcept { return _value; }

    bool set(const T &value) { return (_value != value ? _value = value, true : false); }

    VariantType getVariantType(void) const noexcept override { return VALUE; }

    virtual const String getName(void) const noexcept { return "Value"; }

private:
    T _value;
};