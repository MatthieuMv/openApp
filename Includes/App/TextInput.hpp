/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** TextInput
*/

#pragma once

// Rectangle
#include "App/Rectangle.hpp"
// EventArea
#include "App/EventArea.hpp"
// Text
#include "App/Text.hpp"

namespace oA { class TextInput; }

class oA::TextInput : virtual public oA::Rectangle, virtual public oA::Text, virtual public oA::EventArea
{
public:
    TextInput(void) {
        append("maxLength") = 0;
        get("hCenter") = true;
        get("vCenter") = true;
        get("color") = "white";
        get("fontColor") = "black";
    }

    virtual ~TextInput(void) {}

    virtual String getName(void) const noexcept { return "TextInput"; }

    virtual void draw(IRenderer &renderer) {
        Rectangle::draw(renderer);
        Text::draw(renderer);
    }

    virtual bool onKeyboard(KeyboardEvent &keyboard) {
        if (!*get("focused") || keyboard.state != KeyPressed)
            return false;
        if (interpretCharKey(keyboard) || interpretSpecialKey(keyboard))
            return true;
        return false;
    }
private:
    bool interpretCharKey(KeyboardEvent &keyboard) {
        auto &text = get("text");
        Uint max = get("maxLength")->toInt();
        char c = keyboard.convetToKey();
        if (c && (!max || text->get<String>().length() != max)) {
            text->get<String>().push_back(c);
            text.emit();
            return true;
        }
        return false;
    }

    bool interpretSpecialKey(KeyboardEvent &keyboard) {
        auto &text = get("text");
        switch (keyboard.key) {
        case KeyDelete:
        case KeyBack:
            if (*text) {
                text->get<String>().pop_back();
                text.emit();
            }
            return true;
        default:
            return false;
        }
    }
};