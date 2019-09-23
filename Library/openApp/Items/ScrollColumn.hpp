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
        get("verticalScroll") = true;
        get("width").connect([this] { updateScrollLimit(); return true; });
        get("height").connect([this] { updateScrollLimit(); return true; });
    }

    virtual String getName(void) const noexcept { return "ScrollColumn"; }

protected:
    virtual void onSizeChanged(void) {
        Column::onSizeChanged();
        updateScrollLimit();
    }

private:
    void updateScrollLimit(void) {
        if (_children.empty()) {
            get("scrollMinY") = 0;
            return;
        }
        auto &back = *_children.back();
        auto total = back.getAs<Number>("y") + back.getAs<Number>("height");
        auto height = getAs<Number>("height");
        get("scrollMinY") = total > height ? -total + height * 0.1f : 0;
    }
};