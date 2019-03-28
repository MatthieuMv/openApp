/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Variant
*/

#pragma once

#include "Core/String.hpp"
#include "Core/Scalar.hpp"
#include "Core/Error.hpp"

namespace oA { class Variant; }

class oA::Variant
{
public:
    enum VariantType {
        OBJECT = 0,
        VALUE
    };

    Variant(void) = default;
    virtual ~Variant(void) = default;

    virtual const String getName(void) const noexcept = 0;

    virtual VariantType getVariantType(void) const noexcept { return OBJECT; }
};

namespace oA
{
    template<typename T>
    const T &VGet(const Variant &var) {
        const T *ptr = dynamic_cast<const T *>(&var);
        if (!ptr)
            throw oA::TypeError("Variant", "Couldn't VGet variable " + var.getName());
        return (*ptr);
    }
}