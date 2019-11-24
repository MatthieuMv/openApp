/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Column
*/

#pragma once

#include <openApp/Items/Layout.hpp>
#include <openApp/Core/Log.hpp>

namespace oA { class Column; }

class oA::Column : virtual public Layout
{
public:
    Column(void) { get("horizontal") = false; }

    virtual ~Column(void) = default;

    virtual String getName(void) const noexcept { return "Column"; }
};