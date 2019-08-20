/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Window
*/

#pragma once

#include <openApp/App/Item.hpp>

namespace oA { class Window; }

class oA::Window : virtual public Item
{
public:
    virtual ~Window(void) = default;

    enum EventType {
        Title,
        Color,
        Resize,
        Fullscreen,
        Borderless,
        VSync
    };

    Window(void) {
        (append("title") = "openApp").connect([this] { pushEvent(Title); return true; });
        (append("color") = "white").connect([this] { pushEvent(Color); return true; });
        (append("resize") = true).connect([this] { pushEvent(Resize); return true; });
        (append("fullscreen") = false).connect([this] { pushEvent(Fullscreen); return true; });
        (append("borderless") = false).connect([this] { pushEvent(Borderless); return true; });
        (append("vsync") = false).connect([this] { pushEvent(VSync); return true; });
        get("width") = 600;
        get("height") = 400;
    }

    virtual String getName(void) const noexcept { return "Window"; }

    virtual void onUpdate(IRenderer &renderer) {
        if (getWindowIndex() < 0)
            throw LogicError("Window", "Invalid use of unconfigured @Window@, openApp supports only Window as root item");
        processEvents(renderer);
    }

    virtual bool onEvent(IRenderer &, const Event &event) {
        if (event.getType() != Event::Window)
            return false;
        auto &wnd = event.getAs<WindowEvent>();
        if (wnd.type == WindowEvent::Moved) {
            get("x") = wnd.data.x;
            get("y") = wnd.data.y;
            return true;
        } else if (wnd.type == WindowEvent::Resized) {
            get("width") = wnd.data.x;
            get("height") = wnd.data.y;
            return true;
        }
        return false;
    }

    WindowContext getWindowContext(void) const {
        return WindowContext(
            getAs<Literal>("title").c_str(),
            V2i(getAs<Number>("screenX"), getAs<Number>("screenY")),
            V2i(getAs<Number>("width"), getAs<Number>("height")),
            oA::Color::RetreiveColor(getAs<Literal>("color")),
            getWindowType(),
            get("vsync")
        );
    }

    void setWindowIndex(Int index) { _index = index; }

    Int getWindowIndex(void) const noexcept { return _index; }

private:
    Int _index = -1;
    UMap<EventType, bool> _events;

    void pushEvent(EventType type) { _events[type] = true; }

    void processEvents(IRenderer &renderer) {
        for (auto &event : _events) {
            if (!event.second)
                continue;
            processEvent(renderer, event.first);
        event.second = false;
        }
    }

    void processEvent(IRenderer &renderer, EventType type) {
        switch (type) {
        case Title:
            renderer.setWindowTitle(getWindowIndex(), getAs<Literal>("title").c_str());
            break;
        case Color:
            renderer.setWindowColor(getWindowIndex(), Color::RetreiveColor(getAs<Literal>("color")));
            break;
        case Resize:
        case Fullscreen:
        case Borderless:
            renderer.setWindowType(getWindowIndex(), getWindowType());
            break;
        case VSync:
            renderer.setWindowVSync(getWindowIndex(), get("resize"));
            break;
        }
    }

    WindowContext::WindowType getWindowType(void) const {
        static const UMap<String, WindowContext::WindowType> Types = {
            { "resize", WindowContext::Resizable },
            { "fullscreen", WindowContext::Fullscreen },
            { "borderless", WindowContext::Borderless }
        };

        for (const auto &type : Types) {
            if (get(type.first))
                return type.second;
        }
        return WindowContext::Fixed;
    }
};