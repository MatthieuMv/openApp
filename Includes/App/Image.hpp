/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Image
*/

#pragma once

// Item
#include "App/Item.hpp"

namespace oA { class Image; }

class oA::Image : virtual public oA::Item
{
public:
    Image(void) {
        append("source") = "";
    }

    virtual ~Image(void) {}

    virtual String getName(void) const noexcept { return "Image"; }

    virtual void draw(IRenderer &renderer) {
        ImageContext ctx;
        getImageContext(ctx);
        renderer.drawImage(ctx);
    }

    void getImageContext(ImageContext &ctx) const {
        getItemContext(ctx);
        ctx.source = get("source")->getConst<String>();
    }
};
