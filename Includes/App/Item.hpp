/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include "Core/Scalar.hpp"
#include "Interpreter.hpp"
#include "Property.hpp"
#include "MakeCode.hpp"

namespace oA { class Item; }

class oA::Item
{
    MAKE_PROPERTY(String, id)
    MAKE_PROPERTY(Float, x)
    MAKE_PROPERTY(Float, y)
    MAKE_PROPERTY(Float, width)
    MAKE_PROPERTY(Float, height)

public:
    Item(void) = default;
};