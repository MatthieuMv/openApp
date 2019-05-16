/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Context
*/

#pragma once

// Scalars
#include "Core/Scalar.hpp"
// Strings
#include "Core/String.hpp"
// Color
#include "Core/Colors.hpp"

namespace oA
{
    /* Drawing Contexts
        Theses structures represents raw drawing data used in any IRenderer.
        Every context inherits from ItemContext, it allows dynamic cast over
        each Item's context implementation.
    */
    struct ItemContext;
    struct WindowContext;
    struct RectangleContext;
    struct TextContext;
    struct ImageContext;
}

struct oA::ItemContext
{
    Float x = 0.0f, y = 0.0f;
    Float width = 0.0f, height = 0.0f;
};

struct oA::WindowContext : public oA::ItemContext
{
    bool resizable = false;
};

struct oA::RectangleContext : public oA::ItemContext
{
    Color color;
};

struct oA::TextContext : public oA::ItemContext
{
    String font, text;
    Uint fontSize = 12;
    Color fontColor;
    bool hCenter = false, vCenter = false;
};

struct oA::ImageContext : public oA::ItemContext
{
    String source;
    ItemContext sourceSize;
};
