/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include "Core/Scalar.hpp"
#include "Property.hpp"
#include "MakeCode.hpp"

namespace oA { class Item; }

class oA::Item
{
    MAKE_PROPERTY(String, id)
    MAKE_PROPERTY(Property<Float>, x)
    MAKE_PROPERTY(Property<Float>, y)
    MAKE_PROPERTY(Property<Float>, width)
    MAKE_PROPERTY(Property<Float>, height)

public:
    static void registerItem(void);

public:
    Item(void) {
    }
};