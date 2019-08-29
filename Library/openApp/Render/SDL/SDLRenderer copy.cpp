/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** SDLRenderer
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <openApp/Render/SDL/Extern/SDL_FontCache.h>
#include <openApp/Render/SDL/Extern/SDL2_gfxPrimitives.h>
#include <openApp/Types/Error.hpp>
#include <openApp/Render/SDL/SDLRenderer.hpp>
#include <openApp/Core/Log.hpp>

oA::SDLRenderer::Context::Context(SDL_Window *_window, SDL_Renderer *_renderer, Color _clear)
    : window(_window), renderer(_renderer), clear(_clear)
{
}

oA::SDLRenderer::Context::~Context(void)
{
    clearCache();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

oA::SDLRenderer::Context &oA::SDLRenderer::Context::operator=(Context &&other)
{
    textures = std::move(other.textures)
    fonts = std::move(other.fonts)
    window = other.window;
    renderer = other.renderer;
    clear = other.clear;
    return *this;
}

void oA::SDLRenderer::Context::clearCache(void)
{
    textures.apply([](auto &texture) { SDL_DestroyTexture(texture.second); });
    fonts.apply([](auto &font) { FC_FreeFont(font.second); });
}

oA::SDLRenderer::SDLRenderer(void)
{
    constexpr auto sdlFlags = SDL_INIT_TIMER | SDL_INIT_VIDEO;
    constexpr auto imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;

    if (SDL_Init(sdlFlags) || !IMG_Init(imgFlags) || TTF_Init() < 0)
        throw RuntimeError("SDLRenderer", "Couldn't initialize @SDL@ renderer");
}

oA::SDLRenderer::~SDLRenderer(void)
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void oA::SDLRenderer::setTargetFPS(Float fps)
{
    _fpsDelay = 1000.0f / fps;
}

void oA::SDLRenderer::handleTargetFPS(void)
{
    Uint tick = SDL_GetTicks(), frameTime = tick - _tick;

    if (frameTime < _fpsDelay) {
        SDL_Delay(_fpsDelay - frameTime);
        _tick = SDL_GetTicks();
    } else
        _tick = tick;
}

oA::Int oA::SDLRenderer::openWindow(const WindowContext &context)
{
    auto *window = SDL_CreateWindow(
            context.title,
            context.pos.x, context.pos.y,
            context.size.x, context.size.y,
            getWindowFlags(context.type)
        );

    if (!window)
        throw RuntimeError("SDLRenderer", "Couldn't create @window@");
    auto *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | (context.vsync ? SDL_RENDERER_PRESENTVSYNC : 0)
    );
    if (!renderer)
        throw RuntimeError("SDLRenderer", "Couldn't create @renderer@ for new @window@");
    auto index = SDL_GetWindowID(window);
    _contexts[index] = Context(window, renderer, context.color);
    return index;
}

void oA::SDLRenderer::closeWindow(Int index)
{
    auto it = _contexts.find(index);

    if (it == _contexts.end())
        throw RuntimeError("SDLRenderer", "Couldn't close null @window@");
    if (&it->second == _current)
        _current = nullptr;
    _contexts.erase(it);
}

oA::V2i oA::SDLRenderer::getWindowPos(Int index)
{
    auto it = _contexts.find(index);
    V2i res;

    if (it == _contexts.end())
        throw AccessError("SDLRenderer", "Can't access invalid window index @" + ToString(index) + "@");
    SDL_GetWindowPosition(
        it->second.window,
        &res.x,
        &res.y
    );
    return res;
}

oA::V2i oA::SDLRenderer::getWindowSize(Int index)
{
    auto it = _contexts.find(index);
    V2i res;

    if (it == _contexts.end())
        throw AccessError("SDLRenderer", "Can't access invalid window index @" + ToString(index) + "@");
    SDL_GetWindowSize(
        it->second.window,
        &res.x,
        &res.y
    );
    return res;
}

void oA::SDLRenderer::setWindowPos(Int index, const V2i &pos)
{
    auto it = _contexts.find(index);

    if (it == _contexts.end())
        throw AccessError("SDLRenderer", "Can't access invalid window index @" + ToString(index) + "@");
    SDL_SetWindowPosition(
        it->second.window,
        pos.x,
        pos.y
    );
}

void oA::SDLRenderer::setWindowSize(Int index, const V2i &size)
{
    auto it = _contexts.find(index);

    if (it == _contexts.end())
        throw AccessError("SDLRenderer", "Can't access invalid window index @" + ToString(index) + "@");
    SDL_SetWindowSize(
        it->second.window,
        size.x,
        size.y
    );
}

void oA::SDLRenderer::setWindowTitle(Int index, const char *title)
{
    SDL_SetWindowTitle(getContext(index).window, title);
}

void oA::SDLRenderer::setWindowColor(Int index, Color color)
{
    auto it = _contexts.find(index);

    if (it == _contexts.end())
        throw AccessError("SDLRenderer", "Can't access invalid window index @" + ToString(index) + "@");
    it->second.clear = color;
}

void oA::SDLRenderer::setWindowType(Int index, WindowContext::Type type)
{
    auto *window = getContext(index).window;

    switch (type) {
    case WindowContext::Fixed:
        if (SDL_SetWindowFullscreen(window, 0) < 0)
            break;
        SDL_SetWindowResizable(window, SDL_FALSE);
        return;
    case WindowContext::Resizable:
        if (SDL_SetWindowFullscreen(window, 0) < 0)
            break;
        SDL_SetWindowResizable(window, SDL_TRUE);
        return;
    case WindowContext::Fullscreen:
        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0)
            break;
        return;
    case WindowContext::Borderless:
        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
            break;
        return;
    }
    throw RuntimeError("SDLRenderer", "Couldn't change window type");
}

void oA::SDLRenderer::setWindowVSync(Int index, bool value)
{
    auto &wnd = getContext(index);

    wnd.clearCache();
    SDL_DestroyRenderer(wnd.renderer);
    wnd.renderer = SDL_CreateRenderer(
        wnd.window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | (value ? SDL_RENDERER_PRESENTVSYNC : 0)
    );
    if (!wnd.renderer)
        throw RuntimeError("SDLRenderer", "Couldn't change vsync");
}

void oA::SDLRenderer::clearWindow(Int index)
{
    auto it = _contexts.find(index);

    if (it == _contexts.end())
        throw AccessError("SDLRenderer", "Invalid clear @Window@ index");
    _current = &it->second;
    SDL_SetRenderDrawColor(
        _current->renderer,
        _current->clear.getR(),
        _current->clear.getG(),
        _current->clear.getB(),
        _current->clear.getA()
    );
    SDL_RenderClear(_current->renderer);
}

void oA::SDLRenderer::renderWindow(void)
{
    SDL_RenderPresent(_current->renderer);
}

void oA::SDLRenderer::setClippingArea(const AreaContext &context)
{
    SDL_Rect rect;

    rect.x = context.pos.x;
    rect.y = context.pos.y;
    rect.w = context.size.x;
    rect.h = context.size.y;
    SDL_RenderSetClipRect(_current->renderer, &rect);
}

void oA::SDLRenderer::stopClipping(void)
{
    SDL_RenderSetClipRect(_current->renderer, nullptr);
}

void oA::SDLRenderer::draw(const LineContext &context)
{
    if (context.thick != 1) {
        thickLineColor(
            _current->renderer,
            context.p1.x, context.p1.y,
            context.p2.x, context.p2.y,
            context.thick,
            context.color.getValue()
        );
    } else if (context.antiAliasing) {
        aalineColor(
            _current->renderer,
            context.p1.x, context.p1.y,
            context.p2.x, context.p2.y,
            context.color.getValue()
        );
    } else {
        lineColor(
            _current->renderer,
            context.p1.x, context.p1.y,
            context.p2.x, context.p2.y,
            context.color.getValue()
        );
    }
}

void oA::SDLRenderer::draw(const TriangleContext &context)
{
    if (context.filled) {
        filledTrigonColor(
            _current->renderer,
            context.p1.x, context.p1.y,
            context.p2.x, context.p2.y,
            context.p3.x, context.p3.y,
            context.color.getValue()
        );
    } else if (context.antiAliasing) {
        aatrigonColor(
            _current->renderer,
            context.p1.x, context.p1.y,
            context.p2.x, context.p2.y,
            context.p3.x, context.p3.y,
            context.color.getValue()
        );
    } else {
        trigonColor(
            _current->renderer,
            context.p1.x, context.p1.y,
            context.p2.x, context.p2.y,
            context.p3.x, context.p3.y,
            context.color.getValue()
        );
    }
}

void oA::SDLRenderer::draw(const RectangleContext &context)
{
    if (context.filled) {
        boxColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.pos.x + context.size.x, context.pos.y + context.size.y,
            context.color.getValue()
        );
    } else {
        rectangleColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.pos.x + context.size.x, context.pos.y + context.size.y,
            context.color.getValue()
        );
    }
}

void oA::SDLRenderer::draw(const CircleContext &context)
{
    if (context.filled) {
        filledCircleColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.size,
            context.color.getValue()
        );
    } else if (context.antiAliasing) {
        aacircleColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.size,
            context.color.getValue()
        );
    } else {
        circleColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.size,
            context.color.getValue()
        );
    }
}

void oA::SDLRenderer::draw(const EllipseContext &context)
{
    if (context.filled) {
        filledEllipseColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.size.x, context.size.y,
            context.color.getValue()
        );
    } else if (context.antiAliasing) {
        aaellipseColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.size.x, context.size.y,
            context.color.getValue()
        );
    } else {
        ellipseColor(
            _current->renderer,
            context.pos.x, context.pos.y,
            context.size.x, context.size.y,
            context.color.getValue()
        );
    }
}

void oA::SDLRenderer::draw(const ImageContext &context)
{
    auto *texture = getTexture(context);
    SDL_Rect src;
    SDL_FRect dest;

    src.x = context.sourcePos.x; src.y = context.sourcePos.y;
    src.w = context.sourceSize.x; src.h = context.sourceSize.y;
    dest.x = context.pos.x; dest.y = context.pos.y;
    dest.w = context.size.x; dest.h = context.size.y;
    SDL_RenderCopyExF(
        _current->renderer,
        texture,
        (!src.x && !src.y && !src.w && !src.h ? nullptr : &src),
        &dest,
        context.rotation,
        nullptr,
        context.vflip ? SDL_FLIP_VERTICAL : context.hflip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
}

void oA::SDLRenderer::draw(const LabelContext &context)
{
    FC_Font *font;
    Float x;

    if (!context.font || !*context.font)
        return;
    font = getFont(context);
    switch (context.align) {
    case LabelContext::Left:
        x = context.pos.x; break;
    case LabelContext::Center:
        x = context.pos.x + context.size.x / 2.0f; break;
    case LabelContext::Right:
        x = context.pos.x + context.size.x; break;
    }
    FC_SetDefaultColor(
        font,
        FC_MakeColor(context.fontColor.getR(), context.fontColor.getG(), context.fontColor.getB(), context.fontColor.getA())
    );
    FC_DrawAlign(
        font,
        _current->renderer,
        x,
        context.pos.y + context.size.y / 2.0f - context.fontSize / 2.0f,
        static_cast<FC_AlignEnum>(context.align),
        context.text
    );
}

oA::SDLRenderer::Context &oA::SDLRenderer::getContext(Int index)
{
    auto it = _contexts.find(index);

    if (it == _contexts.end())
        throw AccessError("SDLRenderer", "Can't access invalid window index @" + ToString(index) + "@");
    return it->second;
}

SDL_Texture *oA::SDLRenderer::getTexture(const ImageContext &context)
{
    auto it = _current->textures.findIf([&context](const auto &p) { return p.first == context.source; });

    if (it != _current->textures.end())
        return it->second;
    auto *img = IMG_LoadTexture(_current->renderer, context.source);
    if (!img)
        throw RuntimeError("SDLRenderer", "Couldn't instantiate new texture @" + String(context.source) + "@");
    _current->textures.emplace_back(context.source, img);
    return img;
}

FC_Font *oA::SDLRenderer::getFont(const LabelContext &context)
{
    auto it = _current->fonts.findIf([&context](const auto &key) {
        return key.first == context.font;
    });

    if (it != _current->fonts.end())
        return it->second;
    auto *font = FC_CreateFont();
    if (!font || !FC_LoadFont(
            font,
            _current->renderer,
            context.font,
            context.fontSize,
            FC_MakeColor(context.fontColor.getR(), context.fontColor.getG(), context.fontColor.getB(), context.fontColor.getA()),
            TTF_STYLE_NORMAL
            ))
        throw RuntimeError("SDLRenderer", "Couldn't instantiate new font @" + String(context.font) + "@");
    _current->fonts.emplace_back(context.font, font);
    return font;
}

oA::Uint oA::SDLRenderer::getWindowFlags(WindowContext::Type type)
{
    switch (type) {
    case WindowContext::Resizable:
        return SDL_WINDOW_RESIZABLE;
    case WindowContext::Fullscreen:
        return SDL_WINDOW_FULLSCREEN;
    case WindowContext::Borderless:
        return SDL_WINDOW_BORDERLESS;
    default:
        return 0;
    }
}

bool oA::SDLRenderer::pollEvent(Event &target)
{
    static const UMap<Uint, bool(SDLRenderer::*)(Event &target, SDL_Event &event)> ConstructMap = {
        { SDL_WINDOWEVENT,      &SDLRenderer::constructWindowEvent },
        { SDL_MOUSEBUTTONUP,    &SDLRenderer::constructMouseEvent },
        { SDL_MOUSEBUTTONDOWN,  &SDLRenderer::constructMouseEvent },
        { SDL_MOUSEMOTION,      &SDLRenderer::constructMotionEvent },
        { SDL_MOUSEWHEEL,       &SDLRenderer::constructWheelEvent },
        { SDL_KEYDOWN,          &SDLRenderer::constructKeyboardEvent },
        { SDL_KEYUP,            &SDLRenderer::constructKeyboardEvent }
    };
    SDL_Event evt;

    if (!SDL_PollEvent(&evt))
        return false;
    for (const auto &pair : ConstructMap) {
        if (pair.first != evt.type)
            continue;
        return (this->*pair.second)(target, evt);
    }
    return false;
}

bool oA::SDLRenderer::constructWindowEvent(Event &target, SDL_Event &event)
{
    static const UMap<UByte, WindowEvent::EventType> EventsMap = {
        { SDL_WINDOWEVENT_SHOWN,        WindowEvent::Shown },
        { SDL_WINDOWEVENT_HIDDEN,       WindowEvent::Hidden },
        { SDL_WINDOWEVENT_MOVED,        WindowEvent::Moved },
        { SDL_WINDOWEVENT_RESIZED,      WindowEvent::Resized },
        { SDL_WINDOWEVENT_MINIMIZED,    WindowEvent::Minimized },
        { SDL_WINDOWEVENT_MAXIMIZED,    WindowEvent::Maximized },
        { SDL_WINDOWEVENT_RESTORED,     WindowEvent::Restored },
        { SDL_WINDOWEVENT_ENTER,        WindowEvent::MouseEnter },
        { SDL_WINDOWEVENT_LEAVE,        WindowEvent::MouseLeave },
        { SDL_WINDOWEVENT_FOCUS_GAINED, WindowEvent::KeyboardFocus },
        { SDL_WINDOWEVENT_FOCUS_LOST,   WindowEvent::KeyboardLostFocus },
        { SDL_WINDOWEVENT_CLOSE,        WindowEvent::Close }
    };
    auto it = EventsMap.find(event.window.event);

    if (it == EventsMap.end())
        return false;
    target.emplace<WindowEvent>(
        it->second,
        V2i(event.window.data1, event.window.data2),
        event.window.timestamp
    );
    target.window = event.window.windowID;
    return true;
}

bool oA::SDLRenderer::constructMouseEvent(Event &target, SDL_Event &event)
{
    static const UMap<UByte, MouseEvent::KeyType> EventsMap = {
        { SDL_BUTTON_LEFT,      MouseEvent::Left },
        { SDL_BUTTON_MIDDLE,    MouseEvent::Middle },
        { SDL_BUTTON_RIGHT,     MouseEvent::Right },
        { SDL_BUTTON_X1,        MouseEvent::Button1 },
        { SDL_BUTTON_X2,        MouseEvent::Button2 }
    };
    auto it = EventsMap.find(event.button.button);

    if (it == EventsMap.end())
        return false;
    target.emplace<MouseEvent>(
        event.type == SDL_MOUSEBUTTONDOWN ? MouseEvent::Pressed : MouseEvent::Released,
        it->second,
        V2i(event.button.x, event.button.y),
        event.button.timestamp
    );
    target.window = event.button.windowID;
    return true;
}

bool oA::SDLRenderer::constructMotionEvent(Event &target, SDL_Event &event)
{
    target.emplace<MotionEvent>(
        V2i(event.motion.x, event.motion.y),
        V2i(event.motion.xrel, event.motion.yrel),
        event.motion.timestamp
    );
    target.window = event.motion.windowID;
    return true;
}

bool oA::SDLRenderer::constructWheelEvent(Event &target, SDL_Event &event)
{
    target.emplace<WheelEvent>(
        event.wheel.direction == SDL_MOUSEWHEEL_NORMAL ? WheelEvent::Bottom : WheelEvent::Top,
        V2i(event.wheel.x, event.wheel.y),
        event.wheel.timestamp
    );
    target.window = event.wheel.windowID;
    return true;
}

bool oA::SDLRenderer::constructKeyboardEvent(Event &target, SDL_Event &event)
{
    static const UMap<UByte, KeyboardEvent::KeyType> EventsMap = {
        { SDLK_a, KeyboardEvent::A },
        { SDLK_b, KeyboardEvent::B },
        { SDLK_c, KeyboardEvent::C },
        { SDLK_d, KeyboardEvent::D },
        { SDLK_e, KeyboardEvent::E },
        { SDLK_f, KeyboardEvent::F },
        { SDLK_g, KeyboardEvent::G },
        { SDLK_h, KeyboardEvent::H },
        { SDLK_i, KeyboardEvent::I },
        { SDLK_j, KeyboardEvent::J },
        { SDLK_k, KeyboardEvent::K },
        { SDLK_l, KeyboardEvent::L },
        { SDLK_m, KeyboardEvent::M },
        { SDLK_n, KeyboardEvent::N },
        { SDLK_o, KeyboardEvent::O },
        { SDLK_p, KeyboardEvent::P },
        { SDLK_q, KeyboardEvent::Q },
        { SDLK_r, KeyboardEvent::R },
        { SDLK_s, KeyboardEvent::S },
        { SDLK_t, KeyboardEvent::T },
        { SDLK_u, KeyboardEvent::U },
        { SDLK_v, KeyboardEvent::V },
        { SDLK_w, KeyboardEvent::W },
        { SDLK_x, KeyboardEvent::X },
        { SDLK_y, KeyboardEvent::Y },
        { SDLK_z, KeyboardEvent::Z },
        { SDLK_0, KeyboardEvent::K0 },
        { SDLK_1, KeyboardEvent::K1 },
        { SDLK_2, KeyboardEvent::K2 },
        { SDLK_3, KeyboardEvent::K3 },
        { SDLK_4, KeyboardEvent::K4 },
        { SDLK_5, KeyboardEvent::K5 },
        { SDLK_6, KeyboardEvent::K6 },
        { SDLK_7, KeyboardEvent::K7 },
        { SDLK_8, KeyboardEvent::K8 },
        { SDLK_9, KeyboardEvent::K9 },
        { SDLK_0, KeyboardEvent::N0 },
        { SDLK_1, KeyboardEvent::N1 },
        { SDLK_2, KeyboardEvent::N2 },
        { SDLK_3, KeyboardEvent::N3 },
        { SDLK_4, KeyboardEvent::N4 },
        { SDLK_5, KeyboardEvent::N5 },
        { SDLK_6, KeyboardEvent::N6 },
        { SDLK_7, KeyboardEvent::N7 },
        { SDLK_8, KeyboardEvent::N8 },
        { SDLK_9, KeyboardEvent::N9 },
        { SDLK_UP, KeyboardEvent::Up },
        { SDLK_LEFT, KeyboardEvent::Left },
        { SDLK_RIGHT, KeyboardEvent::Right },
        { SDLK_DOWN, KeyboardEvent::Down },
        { SDLK_ESCAPE, KeyboardEvent::Escape },
        { SDLK_RETURN, KeyboardEvent::Return },
        { SDLK_SPACE, KeyboardEvent::Space },
        { SDLK_BACKSPACE, KeyboardEvent::Backspace }
    };
    auto it = EventsMap.find(event.key.keysym.sym);

    if (it == EventsMap.end())
        return false;
    target.emplace<KeyboardEvent>(
        event.type == SDL_KEYDOWN ? KeyboardEvent::Pressed : KeyboardEvent::Released,
        it->second,
        event.key.timestamp
    );
    target.window = event.window.windowID;
    return true;
}