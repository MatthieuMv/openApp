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
            get("source")->getAs<Literal>(),
            V2f(get("x")->getAs<Number>(), get("y")->getAs<Number>()),
            V2f(get("width")->getAs<Number>(), get("height")->getAs<Number>()),
            V2i(get("sourceX")->getAs<Number>(), get("sourceY")->getAs<Number>()),
            V2i(get("sourceWidth")->getAs<Number>(), get("sourceHeight")->getAs<Number>()),
            get("rotation")->getAs<Number>(),
            get("verticalFlip"),
            get("horizontalFlip")
        );
    }
};