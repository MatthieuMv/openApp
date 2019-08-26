/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Label
*/

#pragma once

#include <openApp/Items/Item.hpp>

namespace oA { class Label; }

class oA::Label : virtual public Item
{
public:
    virtual ~Label(void) = default;

    Label(void) {
        append("text") = "";
        append("font") = "";
        append("fontColor") = "white";
        append("fontSize") = 12;
        append("alignment") = "center";
    }

    virtual String getName(void) const noexcept { return "Label"; }

    virtual void onDraw(IRenderer &renderer) { renderer.draw(getLabelContext()); }

    LabelContext getLabelContext(void) const {
        return LabelContext(
            getAs<Literal>("text").c_str(),
            getAs<Literal>("font").c_str(),
            V2f(getAs<Number>("screenX"), getAs<Number>("screenY")),
            V2f(getAs<Number>("width"), getAs<Number>("height")),
            oA::Color::RetreiveColor(getAs<Literal>("fontColor")),
            getAs<Number>("fontSize"),
            getAlignment()
        );
    }

private:
    LabelContext::Alignment getAlignment(void) const {
        auto &align = getAs<Literal>("alignment");

        if (align == "left")
            return LabelContext::Left;
        else if (align == "center")
            return LabelContext::Center;
        else if (align == "right")
            return LabelContext::Right;
        throw LogicError("Label", "Invalid context value @" + align + "@");
    }
};