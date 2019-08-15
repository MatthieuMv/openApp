/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** SDLRenderer
*/

#pragma once

#include <openApp/Containers/UMap.hpp>
#include <openApp/Containers/Stack.hpp>
#include <openApp/App/IRenderer.hpp>

namespace oA { class SDLRenderer; }

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

class oA::SDLRenderer : public IRenderer
{
public:
    struct Window
    {
        Window(void) = default;
        Window(SDL_Window *win, SDL_Renderer *render, Color color)
            : window(win), renderer(render), clear(color) {}

        Window &operator=(Window &&other) {
            window = other.window;
            renderer = other.renderer;
            clear = other.clear;
            return *this;
        }

        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        Color clear;
    };

    SDLRenderer(void);
    virtual ~SDLRenderer(void);

    virtual Int openWindow(const WindowContext &context);
    virtual void closeWindow(Int index);
    virtual void pushWindow(const WindowContext &context);
    virtual void pollWindow(WindowContext &context);
    virtual void clearWindow(Int index);
    virtual void renderWindow(void);

    virtual void draw(const LineContext &context);
    virtual void draw(const TriangleContext &context);
    virtual void draw(const RectangleContext &context);
    virtual void draw(const CircleContext &context);
    virtual void draw(const EllipseContext &context);
    virtual void draw(const ImageContext &context);

    virtual bool pollEvent(Event &event);

private:
    UMap<Int, Window> _windows;
    Window *_current = nullptr;

    bool processPoll(Event &target);
    bool checkEventStack(Event &target, Int index);

    bool constructWindowEvent(Event &target, SDL_Event &event);
    bool constructMouseEvent(Event &target, SDL_Event &event);
    bool constructMotionEvent(Event &target, SDL_Event &event);
    bool constructWheelEvent(Event &target, SDL_Event &event);
    bool constructKeyboardEvent(Event &target, SDL_Event &event);

};