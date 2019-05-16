/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Text
*/

#pragma once

// Item
#include "App/Item.hpp"

namespace oA { class Text; }

class oA::Text : virtual public oA::Item
{
public:
    Text(void) {
        append("text") = "";
        append("font") = "";
        append("fontColor") = "white";
        append("fontSize") = 12;
        append("hCenter") = false;
        append("vCenter") = false;
    }

    virtual ~Text(void) {}

    virtual String getName(void) const noexcept { return "Text"; }

    virtual void draw(IRenderer &renderer) {
        TextContext ctx;
        getTextContext(ctx);
        renderer.drawText(ctx);
    }

    void getTextContext(TextContext &ctx) const {
        getItemContext(ctx);
        ctx.text = get("text")->getConst<String>();
        ctx.font = get("font")->getConst<String>();
        ctx.fontColor = oA::Color::RetreiveColor(get("fontColor")->getConst<String>());
        ctx.fontSize = get("fontSize")->toInt();
        ctx.hCenter = *get("hCenter");
        ctx.vCenter = *get("vCenter");
    }
};
