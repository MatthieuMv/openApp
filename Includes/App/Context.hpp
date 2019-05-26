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
// V2
#include "Core/V2.hpp"

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
    struct LineContext;
    struct CircleContext;
}

struct oA::ItemContext
{
    V2f pos, size;
};

struct oA::WindowContext : public oA::ItemContext
{
    String title;
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

struct oA::CircleContext
{
    V2f pos;
    Float radius = 0;
    Color color;
    bool filled = true;
};