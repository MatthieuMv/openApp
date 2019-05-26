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
        setTargetContext(idx) - set the target context used in other functions
        isRunning() - return the state of the target context
        clear() - clear the target context
        draw() - render the target context
        pullEvent(evt) - try to retreive an oA::Event from the target context

    */
    virtual bool setTargetContext(Uint idx) = 0;
    virtual bool isRunning(void) const = 0;
    virtual void clear(void) = 0;
    virtual void draw(void) = 0;
    virtual bool pullEvent(Event &evt) = 0;

    /* Window handling:
        pushWindow(ctw, wnd) - push a window creating it and returning its idx
        pullWindow(ctw, wnd) - pull a window's context creating it if not existing
     */
    virtual oA::Uint pushWindow(const WindowContext &ctx) = 0;
    virtual void pullWindow(WindowContext &ctx) = 0;

    /* Drawer:
        draw a single element in window buffer or
    */
    virtual void drawRectangle(const RectangleContext &ctx) = 0;
    virtual void drawText(const TextContext &ctx) = 0;
    virtual void drawImage(const ImageContext &ctx) = 0;
    virtual void drawCircle(const CircleContext &ctx) = 0;

    /* Utils */
    virtual bool supportsMultiContexts(void) const noexcept = 0;
    virtual bool supports3D(void) const noexcept = 0;
};