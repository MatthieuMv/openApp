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
    struct Window
    {
        Window(void) = default;
        Window(SDL_Window *_window, SDL_Renderer *_renderer, Color _clear)
            : window(_window), renderer(_renderer), clear(_clear) {}

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

    using Font = Pair<String, FC_Font *>;

    SDLRenderer(void);
    virtual ~SDLRenderer(void);

    virtual bool supportsMultipleWindows(void) const { return true; }
    virtual bool supports3DRendering(void) const { return true; }

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
    UMap<Int, Window> _windows;
    UMap<String, SDL_Texture *> _textures;
    List<Font> _fonts;
    Window *_current = nullptr;

    Window &getWindow(Int index);
    SDL_Texture *getTexture(const ImageContext &context);
    FC_Font *getFont(const LabelContext &context);
    Uint getWindowFlags(WindowContext::Type type);
    V2f getLabelPosition(const LabelContext &context);

    bool constructWindowEvent(Event &target, SDL_Event &event);
    bool constructMouseEvent(Event &target, SDL_Event &event);
    bool constructMotionEvent(Event &target, SDL_Event &event);
    bool constructWheelEvent(Event &target, SDL_Event &event);
    bool constructKeyboardEvent(Event &target, SDL_Event &event);
};