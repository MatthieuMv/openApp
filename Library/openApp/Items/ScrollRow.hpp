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
        append("totalWidth") = 0.0f;
        get("horizontalScroll") = true;
        setExpression("scrollMaxX", "-totalWidth");
    }

    virtual String getName(void) const noexcept { return "ScrollRow"; }

protected:
    virtual void onSizeChanged(void) {
        Row::onSizeChanged();
        updateTotalWidth();
    }

private:
    void updateTotalWidth(void) {
        Float total = 0.0f;
        _children.apply([&total](const ItemPtr &child) { total += child->getAs<Number>("width"); });
        get("totalWidth") = total;
    }
};