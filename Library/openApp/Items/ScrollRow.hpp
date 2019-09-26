/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ScrollRow
*/

#pragma once

#include <openApp/Items/ScrollLayout.hpp>
#include <openApp/Items/Row.hpp>

namespace oA { class ScrollRow; }

class oA::ScrollRow : virtual public ScrollLayout, virtual public Row
{
public:
    virtual ~ScrollRow(void) = default;

    ScrollRow(void) {
        get("horizontalScroll") = true;
    }

    virtual String getName(void) const noexcept { return "ScrollRow"; }

private:
    virtual void updateLayout(void) {
        Row::updateLayout();
        if (_children.empty()) {
            get("scrollMaxX") = 0;
            return;
        }
        auto &back = *_children.back();
        auto total = back.getAs<Number>("x") + back.getAs<Number>("width");
        auto width = getAs<Number>("width");
        get("scrollMaxX") = total > width ? -total + width * 0.1f : 0;
    }
};