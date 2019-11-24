/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Layout
*/

#pragma once

#include <openApp/Items/Item.hpp>

namespace oA { class Layout; }

class oA::Layout : virtual public Item
{
public:
    virtual ~Layout(void) = default;

    Layout(void) {
        append("fillWidth") = false;
        append("fillHeight") = false;
        append("fill") = false;
        append("deltaX") = 0.0f;
        append("deltaY") = 0.0f;
        append("padding") = 0;
        append("children") = 0;
        append("horizontal") = false;
        setExpression("paddingX", "padding");
        setExpression("paddingY", "padding");
        get("width").connect([this] { updateLayout(); return true; });
        get("height").connect([this] { updateLayout(); return true; });
    }

    virtual String getName(void) const noexcept { return "Layout"; }

    virtual void onAppendChild(Item &child) override {
        Item::onAppendChild(child);
        resetChildrenSize();
    }

    virtual void onRemoveChild(Item &item) override {
        Item::onRemoveChild(item);
        resetChildrenSize();
    }

    virtual void onSizeChanged(void) {
        get("children") = children().size();
        updateLayout();
    }

    virtual void setChildScreenPos(Item &child) override {
        child.setExpression("screenX", "parent.screenX + parent.deltaX + x");
        child.setExpression("screenY", "parent.screenY + parent.deltaY + y");
    }

    virtual void updateLayout(void) {
        if (get("horizontal"))
            updateRowLayout();
        else
            updateColumnLayout();
    }

private:
    void resetChildrenSize(void) {
        bool fillWidth = get("fillWidth"), fillHeight = get("fillHeight");
        bool paddingX = get("paddingX"), paddingY = get("paddingY");
        bool horizontal = get("horizontal");
        for (auto &child : _children) {
            if (fillWidth)
                child->get("width").clearTree();
            if (fillHeight)
                child->get("height").clearTree();
            if (horizontal || paddingX)
                child->get("x").clearTree();
            if (!horizontal || paddingY)
                child->get("y").clearTree();
        }
    }

    void updateColumnLayout(void) {
        bool fill = get("fill"), fillWidth = fill || get("fillWidth"), fillHeight = fill || get("fillHeight");
        bool hasPaddingX = get("paddingX");
        for (auto it = _children.begin(); it != _children.end(); ++it) {
            auto &child = **it;
            if (fillWidth)
                child.setExpression("width", "parent.width - parent.paddingX * 2", "Column width");
            if (fillHeight)
                child.setExpression("height", "(parent.height - (parent.children + 1) * parent.paddingY) / parent.children", "Column height");
            if (hasPaddingX)
                child.setExpression("x", "parent.paddingX", "Column x");
            if (it == _children.begin())
                child.setExpression("y", "parent.paddingY", "Column y");
            else {
                auto prev = it - 1;
                child.setExpression("y", (*prev)->getID() + ".y + " + (*prev)->getID() + ".height + parent.paddingY", "Column y");
            }
        }
    }

    void updateRowLayout(void) {
        bool fill = get("fill"), fillWidth = fill || get("fillWidth"), fillHeight = fill || get("fillHeight");
        bool paddingY = get("paddingY");
        for (auto it = _children.begin(); it != _children.end(); ++it) {
            auto &child = **it;
            if (fillWidth)
                child.setExpression("width", "(parent.width - (parent.children + 1) * parent.paddingX) / parent.children", "Row width");
            if (fillHeight)
                child.setExpression("height", "parent.height - parent.paddingY * 2", "Row height");
            if (paddingY)
                child.setExpression("y", "parent.paddingY", "Row y");
            if (it == _children.begin())
                child.setExpression("x", "parent.paddingX", "Row x");
            else {
                auto prev = it - 1;
                child.setExpression("x", (*prev)->getID() + ".x + " + (*prev)->getID() + ".width + parent.paddingX", "Row x");
            }
        }
    }
};