/*
** EPITECH PROJECT, 2019
** TeamfightArena
** File description:
** DragArea
*/

#pragma once

#include <openApp/Items/EventArea.hpp>

namespace oA { class DragArea; }

class oA::DragArea : virtual public EventArea
{
public:
    virtual ~DragArea(void) = default;

    DragArea(void) {
        auto &draging = append("draging") = false; // Will be true while draging
        append("dragable") = true; // If true will process drag events
        get("pressed").connect([this] { if (!get("pressed") && get("draging")) onDrop(); return true; });
        draging.connect([this] { if (get("draging")) onDrag(); return true; });
    }

    virtual String getName(void) const noexcept { return "DragArea"; }

    virtual bool onEvent(const Event &event) {
        bool res = EventArea::onEvent(event);
        if (!get("dragable") || !get("pressed") || event.getType() != Event::Motion)
            return res;
        get("draging") = true;
        auto pos = event.getAs<MotionEvent>().pos;
        get("x") = pos.x - getAs<Number>("width") / 2.0f;
        get("y") = pos.y - getAs<Number>("height") / 2.0f;
        return true;
    }

    virtual void onDrag(void) {
        auto *root = getRoot();
        auto index = getMyselfAsIndex();
        auto &x = get("x"), &y = get("y");
        _tmpParent = getParent();
        auto me = getParent()->extractChild(index);
        _tmpX.clearTree();
        x.swap(_tmpX);
        _tmpY.clearTree();
        y.swap(_tmpY);
        root->appendChild(std::move(me));
    }

    virtual void onDrop(void) {
        auto *root = getRoot();
        auto me = getParent()->extractChild(getMyselfAsIndex());
        Event event;
        event.emplace<DropEvent>(ItemPtr(me), getCenterPos());
        get("draging") = false;
        if (root->propagate(event))
            return;
        auto &x = get("x"), &y = get("y");
        x.clearTree(); x.swap(_tmpX);
        y.clearTree(); y.swap(_tmpY);
        _tmpParent->appendChild(std::move(me));
    }

private:
    Property _tmpX, _tmpY;
    Item *_tmpParent = nullptr;

    Uint getMyselfAsIndex(void) {
        Uint index = 0;
        if (!getParent())
            throw LogicError("Dragarea", "Root Item can't be draged");
        getParent()->children().findIf([this, &index](const auto &child) {
            if (this == child.get())
                return true;
            ++index;
            return false;
        });
        return index;
    }

    V2i getCenterPos(void) const {
        return V2i(
            getAs<Number>("x") - getAs<Number>("width") / 2.0f,
            getAs<Number>("y") - getAs<Number>("height") / 2.0f
        );
    }
};