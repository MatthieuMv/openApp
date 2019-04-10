/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#pragma once

#include "Core/Scalar.hpp"
#include "Property.hpp"
#include "PropertyGen.hpp"

namespace oA { class Item; }

class oA::Item
{
    MAKE_PROPERTY(String, id)

public:
    static void registerItem(void);

public:
    Item(void) {
    }
};