/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Image
*/

#pragma once

#include <openApp/App/Item.hpp>
#include <openApp/App/RenderContexts.hpp>

namespace oA { class Image; }

class oA::Image : virtual public Item
{
public:
    virtual ~Image(void) = default;

    Image(void) {
        append("source") = String(); // Image path
        append("sourceX") = 0; // Texture rectangle x
        append("sourceY") = 0; // Texture rectangle y
        append("sourceWidth") = 0; // Texture rectangle width
        append("sourceHeight") = 0; // Texture rectangle height
        append("rotation") = 0.0f; // Image rotation
        append("verticalFlip") = false; // Vertical image flip
        append("horizontalFlip") = false; // Horizontal image flip
    }

    virtual String getName(void) const noexcept { return "Image"; }

    virtual void onDraw(IRenderer &renderer) { renderer.draw(getImageContext()); }

    ImageContext getImageContext(void) const {
        return ImageContext(
            getAs<Literal>("source"),
            V2f(getAs<Number>("x"), getAs<Number>("y")),
            V2f(getAs<Number>("width"), getAs<Number>("height")),
            V2i(getAs<Number>("sourceX"), getAs<Number>("sourceY")),
            V2i(getAs<Number>("sourceWidth"), getAs<Number>("sourceHeight")),
            getAs<Number>("rotation"),
            get("verticalFlip"),
            get("horizontalFlip")
        );
    }
};