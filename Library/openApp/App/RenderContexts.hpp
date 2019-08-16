/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Contexts
*/

#pragma once

#include <openApp/Types/V2.hpp>
#include <openApp/Types/Color.hpp>

namespace oA
{
    struct Context;
    struct AreaContext;
    struct WindowContext;
    struct LineContext;
    struct TriangleContext;
    struct RectangleContext;
    struct CircleContext;
    struct EllipseContext;
    struct ImageContext;
}

struct oA::Context {};

struct oA::AreaContext : public Context
{
    AreaContext(void) = default;
    AreaContext(const V2f &_pos, const V2f &_size) : pos(_pos), size(_size) {}

    V2f pos, size;
};

struct oA::WindowContext : public Context
{
    WindowContext(void) = default;
    WindowContext(const String &_title, const V2i &_pos, const V2i &_size, Color _color, bool _resize, bool _fullscreen)
        : title(_title), pos(_pos), size(_size), color(_color), resize(_resize), fullscreen(_fullscreen) {}

    String title;
    V2i pos, size;
    Color color;
    bool resize = false;
    bool fullscreen = false;
};

struct oA::LineContext : public Context
{
    LineContext(void) = default;
    LineContext(const V2f &_p1, const V2f &_p2, Color _color, Uint _width, bool _antiAliasing)
        : p1(_p1), p2(_p2), color(_color), width(_width), antiAliasing(_antiAliasing) {}

    V2f p1;
    V2f p2;
    Color color;
    Uint width = 0;
    bool antiAliasing = true;
};

struct oA::TriangleContext : public Context
{
    TriangleContext(void) = default;
    TriangleContext(const V2f &_p1, const V2f &_p2, const V2f &_p3, Color _color, bool _filled, bool _antiAliasing)
        : p1(_p1), p2(_p2), p3(_p3), color(_color), filled(_filled), antiAliasing(_antiAliasing) {}

    V2f p1;
    V2f p2;
    V2f p3;
    Color color;
    bool filled = true;
    bool antiAliasing = true;
};

struct oA::RectangleContext : public Context
{
    RectangleContext(void) = default;
    RectangleContext(const V2f &_pos, const V2f &_size, Color _color, bool _filled)
        : pos(_pos), size(_size), color(_color), filled(_filled) {}

    V2f pos;
    V2f size;
    Color color;
    bool filled = true;
};

struct oA::CircleContext : public Context
{
    CircleContext(void) = default;
    CircleContext(const V2f &_pos, Uint _size, Color _color, bool _filled, bool _antiAliasing)
        : pos(_pos), size(_size), color(_color), filled(_filled), antiAliasing(_antiAliasing) {}

    V2f pos;
    Uint size = 0;
    Uint width = 0;
    Color color;
    bool filled = true;
    bool antiAliasing = true;
};

struct oA::EllipseContext : public Context
{
    EllipseContext(void) = default;
    EllipseContext(const V2f &_pos, const V2f &_size, Color _color, bool _filled, bool _antiAliasing)
        : pos(_pos), size(_size), color(_color), filled(_filled), antiAliasing(_antiAliasing) {}

    V2f pos;
    V2f size;
    Uint width = 0;
    Color color;
    bool filled = true;
    bool antiAliasing = true;
};

struct oA::ImageContext : public Context
{
    V2f pos;
    V2f size;
    String source;
};
