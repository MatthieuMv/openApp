/*
** EPITECH PROJECT, 2019
** TeamfightArena
** File description:
** DragArea
*/

#pragma once

#include <openApp/Core/Log.hpp>
#include <openApp/Items/EventArea.hpp>

namespace oA { class DragArea; }

class oA::DragArea : virtual public EventArea
{
public:
    virtual ~DragArea(void) = default;

    DragArea(void) {
        append("draggable") = true; // If true will process drag events
        append("dragging") = false; // Will be true while dragging
        append("dragged"); // Event on drag
        append("catched"); // Event on drop
        append("canceled"); // Event on drop failure
    }

    virtual String getName(void) const noexcept { return "DragArea"; }

    virtual bool onEvent(const Event &event) {
        bool res = EventArea::onEvent(event);
        if (!get("draggable"))
            return res;
        if (get("dragging") && event.getType() == Event::Motion) {
            updateCoord(event.getAs<MotionEvent>().pos);
            return res;
        } else if (event.getType() == Event::Mouse)
            return handleMouseEvent(event.getAs<MouseEvent>()) || res;
        return res;
    }

private:
    Property _oldX, _oldY;
    Item *_oldParent = nullptr;

    void updateCoord(const V2i &pos) {
        get("x") = pos.x - getAs<Number>("width") / 2.0f;
        get("y") = pos.y - getAs<Number>("height") / 2.0f;
    }

    bool handleMouseEvent(const MouseEvent &event) {
        if (event.type == MouseEvent::Released && get("dragging"))
            return onDrop(event.pos);
        else if (event.type != MouseEvent::Pressed || get("dragging") || !get("hovered"))
            return false;
        onDrag();
        updateCoord(event.pos);
        return true;
    }

    void onDrag(void) {
        auto *root = getRoot();
        _oldParent = getParent();
        auto me = _oldParent->extractChild(getMyIndex());
        saveDragState();
        root->appendChild(std::move(me));
        get("dragging") = true;
        get("dragged").call();
    }

    bool onDrop(const V2i &pos) {
        auto *root = getRoot();
        auto me = getParent()->extractChild(getMyIndex());
        Event event;
        revertDragState();
        get("dragging") = false;
        event.emplace<DropEvent>(ItemPtr(me), pos);
        if (root->propagate(event)) {
            get("catched").call();
            return true;
        }
        get("x") = _oldX;
        get("y") = _oldY;
        _oldParent->appendChild(std::move(me));
        get("canceled").call();
        return false;
    }

    UInt getMyIndex(void) const {
        UInt index = 0;
        if (!getParent())
            throw LogicError("DragArea", "Can't get @index@ of DragArea that doesn't have @parent@");
        getParent()->children().findIf([this, &index](const auto &child) {
            if (this == child.get())
                return true;
            ++index;
            return false;
        });
        return index;
    }

    void saveDragState(void) {
        _oldX.clearTree();
        _oldY.clearTree();
        get("x").swap(_oldX);
        get("y").swap(_oldY);
    }

    void revertDragState(void) {
        auto &x = get("x"), &y = get("y");
        Var cache;
        x.swap(_oldX);
        y.swap(_oldY);
        _oldX.clearTree();
        _oldY.clearTree();
        cache = std::move(x);
        x = _oldX;
        _oldX = std::move(cache);
        cache = std::move(y);
        y = _oldY;
        _oldY = std::move(cache);
    }
};