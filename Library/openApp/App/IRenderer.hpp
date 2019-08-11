/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IRenderer
*/

#pragma once

#include <openApp/App/Contexts.hpp>

namespace oA { class IRenderer; }

class oA::IRenderer
{
public:
    virtual ~IRenderer(void) = default;

    /**
     * @brief Open a new window
     *
     * @param context Window context
     * @return Uint Window ID
     */
    virtual Uint addWindow(const WindowContext &context) = 0;

    /**
     * @brief Set internal window target
     *
     * @param index Window's index
     */
    virtual void useWindow(Uint index) = 0;

    virtual void drawLine(const LineContext &context) = 0;
    virtual void drawTriangle(const TriangleContext &context) = 0;
    virtual void drawRectangle(const RectangleContext &context) = 0;
    virtual void drawCircle(const CircleContext &context) = 0;
};