/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IRenderer
*/

#pragma once

// Shared
#include "Core/Memory.hpp"
// Uint
#include "Core/Scalar.hpp"
// Event
#include "App/Event.hpp"
// Context
#include "App/Context.hpp"

namespace oA
{
    class IRenderer;

    using IRendererPtr = Shared<IRenderer>;
}

class oA::IRenderer
{
public:
    virtual ~IRenderer(void) = default;

    /* Core:
        isRunning(wnd) - return the state of a window
        clear(wnd) - clear a window
        draw() - render a window
        pullEvent(evt, wnd) - try to retreive an oA::Event from a window

    */
    virtual bool isRunning(Uint idx = 0) const = 0;
    virtual void clear(Uint idx = 0) = 0;
    virtual void draw(Uint idx = 0) = 0;
    virtual bool pullEvent(Event &evt, Uint idx = 0) = 0;

    /* Window handling:
        pushWindow(ctw, wnd) - push a window creating it and returning its idx
        pullWindow(ctw, wnd) - pull a window's context creating it if not existing
     */
    virtual oA::Uint pushWindow(const WindowContext &ctx) = 0;
    virtual void pullWindow(WindowContext &ctx, Uint idx = 0) = 0;

    /* Drawer:
        draw a single element in window buffer or
    */
    virtual void drawRectangle(const RectangleContext &ctx, Uint idx = 0) = 0;
    virtual void drawText(const TextContext &ctx, Uint idx = 0) = 0;
    virtual void drawImage(const ImageContext &ctx, Uint idx = 0) = 0;
};