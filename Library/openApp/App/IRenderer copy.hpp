/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IRenderer
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/App/RenderContexts.hpp>
#include <openApp/App/Event.hpp>

namespace oA
{
    class IRenderer;

    using IRendererPtr = Unique<IRenderer>;
}

class oA::IRenderer
{
public:
    virtual ~IRenderer(void) = default;

    /**
     * @brief Open a new window and set it as current target window
     *
     * @param context Window's context
     * @return Int Window's index
     */
    virtual Int openWindow(const WindowContext &context) = 0;

    /**
     * @brief Close a window
     *
     * @param index Close current target window
     */
    virtual void closeWindow(void) = 0;

    /**
     * @brief Set current window target (that will be used for rendering and event handling)
     *
     * @param index Window's index
     */
    virtual void useWindow(Int index) = 0;

    /**
     * @brief Push a window context
     *
     * @param context Current target window context patch
     */
    virtual void pushWindow(const WindowContext &context) = 0;

    /**
     * @brief Poll informations of current target window
     *
     * @param context Current target window's context target
     */
    virtual void pollWindow(WindowContext &context) = 0;

    /**
     * @brief Clear current target window
     */
    virtual void clearWindow(void) = 0;

    /**
     * @brief Renderer current target window
     */
    virtual void renderWindow(void) = 0;

    /**
     * @brief Draw Line in current target window
     *
     * @param context Line data
     */
    virtual void draw(const LineContext &context) = 0;

    /**
     * @brief Draw Triangle in current target window
     *
     * @param context Triangle data
     */
    virtual void draw(const TriangleContext &context) = 0;

    /**
     * @brief Draw Rectangle in current target window
     *
     * @param context Rectangle data
     */
    virtual void draw(const RectangleContext &context) = 0;

    /**
     * @brief Draw Circle in current target window
     *
     * @param context Circle data
     */
    virtual void draw(const CircleContext &context) = 0;

    /**
     * @brief Draw Ellipse in current target window
     *
     * @param context Ellipse data
     */
    virtual void draw(const EllipseContext &context) = 0;

    /**
     * @brief Draw Image in current target window
     *
     * @param context Image data
     */
    virtual void draw(const ImageContext &context) = 0;

    /**
     * @brief Poll an event from current target window
     *
     * @param target Event to fill in
     * @return true An event has been polled
     * @return false No event has been polled
     */
    virtual bool pollEvent(Event &target) = 0;
};