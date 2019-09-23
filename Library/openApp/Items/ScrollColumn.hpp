/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ScrollColumn
*/

#pragma once

#include <openApp/Items/ScrollLayout.hpp>
#include <openApp/Items/Column.hpp>

namespace oA { class ScrollColumn; }

class oA::ScrollColumn : virtual public ScrollLayout, virtual public Column
{
public:
    virtual ~ScrollColumn(void) = default;

    ScrollColumn(void) {
        append("totalHeight") = 0.0f;
        get("verticalScroll") = true;
        setExpression("scrollMinY", "-totalHeight");
    }

    virtual String getName(void) const noexcept { return "ScrollColumn"; }

protected:
    virtual void onSizeChanged(void) {
        Column::onSizeChanged();
        updateTotalHeight();
    }

private:
    void updateTotalHeight(void) {
        Float total = 0.0f;
        _children.apply([&total](const ItemPtr &child) { total += child->getAs<Number>("height"); });
        get("totalHeight") = total;
    }
};