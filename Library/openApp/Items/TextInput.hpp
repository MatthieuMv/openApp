/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** TextInput
*/

#pragma once

#include <openApp/Items/Button.hpp>
#include <openApp/Core/Log.hpp>

namespace oA { class TextInput; }

class oA::TextInput : public Button
{
public:
    virtual ~TextInput(void) = default;

    TextInput(void) {
        append("focused") = false;
        get("released").connect([this] {
            get("focused") = true;
            return true;
        });
        get("color") = "white";
        get("fontColor") = "black";
        get("borderWidth") = 1;
    }

    virtual String getName(void) const noexcept { return "TextInput"; }

    virtual bool onEvent(IRenderer &renderer, const Event &event) {
        bool res = Button::onEvent(renderer, event);
        if (res || !get("focused"))
            return res;
        else if (event.getType() == Event::Mouse && !contains(event.getAs<MouseEvent>().pos)) {
            get("focused") = false;
            renderer.setTextInputState(false);
            return false;
        } else if (event.getType() == Event::Keyboard)
            return handleKeyEvent(event.getAs<KeyboardEvent>());
        else if (event.getType() == Event::Text)
            return handleTextEvent(event.getAs<TextEvent>());
        return res;
    }

    virtual void onUpdate(IRenderer &renderer) {
        if (get("focused"))
            renderer.setTextInputState(true);
    }

private:
    bool handleKeyEvent(const KeyboardEvent &event) {
        if (event.type == KeyboardEvent::Released)
            return false;
        switch (event.key) {
        case KeyboardEvent::Backspace:
            get("text").pop();
            return true;
        default:
            return false;
        }
    }

    bool handleTextEvent(const TextEvent &event) {
        get("text") += event.input;
        return true;
    }
};