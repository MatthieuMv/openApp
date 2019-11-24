/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Row
*/

#pragma once

#include <openApp/Items/Layout.hpp>

namespace oA { class Row; }

class oA::Row : virtual public Layout
{
public:
    Row(void) { get("horizontal") = true; }

    virtual ~Row(void) = default;

    virtual String getName(void) const noexcept { return "Row"; }
};