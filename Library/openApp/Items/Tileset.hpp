/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Tileset
*/

#pragma once

#include <openApp/Items/Image.hpp>

namespace oA { class Tileset; }

class oA::Tileset : virtual public Image
{
public:
    virtual ~Tileset(void) = default;

    Tileset(void) {
        append("xIndex") = 0;
        append("yIndex") = 0;
        setExpression("sourceX", "sourceWidth * xIndex");
        setExpression("sourceY", "sourceHeight * yIndex");
    }

    virtual String getName(void) const noexcept { return "Tileset"; }
};