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
    struct LabelContext;
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
    enum Type {
        Fixed,
        Resizable,
        Fullscreen,
        Borderless
    };

    WindowContext(void) = default;
    WindowContext(const char *_title, const V2i &_pos, const V2i &_size, Color _color, Type _type = Resizable, bool _vsync = true)
        : title(_title), pos(_pos), size(_size), color(_color), type(_type), vsync(_vsync) {}

    const char *title = nullptr;
    V2i pos, size;
    Color color;
    Type type = Resizable;
    bool vsync = true;
};

struct oA::LineContext : public Context
{
    LineContext(void) = default;
    LineContext(const V2f &_p1, const V2f &_p2, Color _color, Uint _thick, bool _antiAliasing)
        : p1(_p1), p2(_p2), color(_color), thick(_thick), antiAliasing(_antiAliasing) {}

    V2f p1;
    V2f p2;
    Color color;
    Uint thick = 0;
    bool antiAliasing = true;
};

struct oA::TriangleContext : public Context
{
    TriangleContext(void) = default;
    TriangleContext(const V2f &_p1, const V2f &_p2, const V2f &_p3, Color _color, bool _filled = true, bool _antiAliasing = true)
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
    RectangleContext(const V2f &_pos, const V2f &_size, Color _color, bool _filled = true)
        : pos(_pos), size(_size), color(_color), filled(_filled) {}

    V2f pos;
    V2f size;
    Color color;
    bool filled = true;
};

struct oA::CircleContext : public Context
{
    CircleContext(void) = default;
    CircleContext(const V2f &_pos, Uint _size, Color _color, bool _filled = true, bool _antiAliasing = true)
        : pos(_pos), size(_size), color(_color), filled(_filled), antiAliasing(_antiAliasing) {}

    V2f pos;
    Uint size = 0;
    Color color;
    bool filled = true;
    bool antiAliasing = true;
};

struct oA::EllipseContext : public Context
{
    EllipseContext(void) = default;
    EllipseContext(const V2f &_pos, const V2f &_size, Color _color, bool _filled = true, bool _antiAliasing = true)
        : pos(_pos), size(_size), color(_color), filled(_filled), antiAliasing(_antiAliasing) {}

    V2f pos;
    V2f size;
    Color color;
    bool filled = true;
    bool antiAliasing = true;
};

struct oA::ImageContext : public Context
{
    ImageContext(void) = default;
    ImageContext(const char *_source, const V2f &_pos, const V2f &_size, const V2i &_sourcePos = V2i(), const V2i &_sourceSize = V2i(), Float _rotation = 0, bool _vflip = false, bool _hflip = false)
        : source(_source), pos(_pos), size(_size), sourcePos(_sourcePos), sourceSize(_sourceSize), rotation(_rotation), vflip(_vflip), hflip(_hflip) {}

    const char *source = nullptr;
    V2f pos;
    V2f size;
    V2i sourcePos;
    V2i sourceSize;
    Float rotation = 0;
    bool vflip = false, hflip = false;
};

struct oA::LabelContext : public Context
{
    enum Alignment {
        Left,
        Center,
        Right
    };

    LabelContext(void) = default;
    LabelContext(const char *_text, const char *_font, const V2f &_pos, const V2f &_size, Color _fontColor, Uint _fontSize = 12, Alignment _align = Center)
        : text(_text), font(_font), pos(_pos), size(_size), fontColor(_fontColor), fontSize(_fontSize), align(_align) {}

    const char *text = nullptr;
    const char *font = nullptr;
    V2f pos;
    V2f size;
    Color fontColor;
    Uint fontSize = 12;
    Alignment align = Center;
};