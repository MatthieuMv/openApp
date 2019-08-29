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
        append("draggable") = true; // If true will process drag events
        append("dragging") = false; // Will be true while dragging
        append("dragged"); // Event on drag
        append("dropped"); // Event on drop
        append("catched"); // Event on drop catching
        append("failed"); // Event on drop failure
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
        if (event.type == MouseEvent::Released && get("dragging")) {
            return onDrop();
        } else if (event.type == MouseEvent::Pressed && !get("dragging") && get("hovered")) {
            onDrag();
            updateCoord(event.pos);
            return !get("propagate");
        }
        return false;
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

    bool onDrop(void) {
        auto *root = getRoot();
        auto me = getParent()->extractChild(getMyIndex());
        Event event;
        get("dragging") = false;
        get("dropped").call();
        event.emplace<DropEvent>(ItemPtr(me), getCenterPos());
        if (root->propagate(event)) {
            get("catched").call();
            return true;
        }
        revertDragState(me);
        get("failed").call();
        return false;
    }

    V2i getCenterPos(void) const {
        return V2i(
            getAs<Number>("x") - getAs<Number>("width") / 2.0f,
            getAs<Number>("y") - getAs<Number>("height") / 2.0f
        );
    }

    Uint getMyIndex(void) const {
        Uint index = 0;
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

    void revertDragState(ItemPtr &me) {
        auto &x = get("x"), &y = get("y");
        x.clearTree();
        x.swap(_oldX);
        y.clearTree();
        y.swap(_oldY);
        _oldParent->appendChild(std::move(me));
    }
};