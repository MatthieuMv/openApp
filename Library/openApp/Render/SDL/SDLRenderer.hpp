/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** SDLRenderer
*/

#pragma once

#include <openApp/Containers/List.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Containers/Stack.hpp>
#include <openApp/Render/IRenderer.hpp>

namespace oA { class SDLRenderer; }

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct FC_Font;
union SDL_Event;

class oA::SDLRenderer : public IRenderer
{
public:
    struct RenderContext
    {
        RenderContext(void) = default;
        RenderContext(SDL_Window *_window, SDL_Renderer *_renderer, Color _clear);
        ~RenderContext(void);

        RenderContext &operator=(RenderContext &&other);

        void destroy(void);
        void clearCache(void);

        List<Pair<String, SDL_Texture *>> textures;
        List<Pair<Pair<String, UInt>, FC_Font *>> fonts;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        Color clear;
    };

    SDLRenderer(void);
    virtual ~SDLRenderer(void);

    virtual bool supportsMultipleWindows(void) const { return true; }
    virtual bool supports3DRendering(void) const { return true; }

    virtual void setTargetFPS(Float fps);
    virtual void handleTargetFPS(void);
    virtual Int openWindow(const WindowContext &context);
    virtual void closeWindow(Int index);
    virtual V2i getWindowSize(Int index);
    virtual V2i getWindowPos(Int index);
    virtual void setWindowPos(Int index, const V2i &pos);
    virtual void setWindowSize(Int index, const V2i &size);
    virtual void setWindowTitle(Int index, const char *title);
    virtual void setWindowColor(Int index, Color color);
    virtual void setWindowType(Int index, WindowContext::Type type);
    virtual void setWindowVSync(Int index, bool value);

    virtual void clearWindow(Int index);
    virtual void renderWindow(void);

    virtual void setClippingArea(const AreaContext &context);
    virtual void stopClipping(void);

    virtual void draw(const LineContext &context);
    virtual void draw(const TriangleContext &context);
    virtual void draw(const RectangleContext &context);
    virtual void draw(const CircleContext &context);
    virtual void draw(const EllipseContext &context);
    virtual void draw(const ImageContext &context);
    virtual void draw(const LabelContext &context);

    virtual bool pollEvent(Event &event);

private:
    UMap<Int, RenderContext> _contexts;
    RenderContext *_current = nullptr;
    Float _fpsDelay = 1000.0f / 60.0f;
    UInt _tick = 0;

    RenderContext &getRenderContext(Int index);
    SDL_Texture *getTexture(const ImageContext &context);
    FC_Font *getFont(const LabelContext &context);
    UInt getWindowFlags(WindowContext::Type type);

    bool constructWindowEvent(Event &target, SDL_Event &event);
    bool constructMouseEvent(Event &target, SDL_Event &event);
    bool constructMotionEvent(Event &target, SDL_Event &event);
    bool constructWheelEvent(Event &target, SDL_Event &event);
    bool constructKeyboardEvent(Event &target, SDL_Event &event);
};