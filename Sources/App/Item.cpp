/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

// Item
#include "App/Item.hpp"

void oA::Item::render(IRenderer &renderer)
{
    if (!*get("visible"))
        return;
    draw(renderer);
    for (auto &child : _childs) {
        child->render(renderer);
    }
}

bool oA::Item::propagate(Event &evt)
{
    for (auto &child : _childs) {
        if (child->propagate(evt))
            return true;
    }
    return onEvent(evt);
}

bool oA::Item::contains(Float x, Float y) const noexcept
{
    auto screenX = get("screenX")->getConst<Float>(), screenY = get("screenY")->getConst<Float>();
    return (
        x >= screenX && x <= (screenX + get("width")->getConst<Float>()) &&
        y >= screenY && y <= (screenY + get("height")->getConst<Float>())
    );
}

void oA::Item::getItemContext(ItemContext &ctx) const
{
    ctx.x = get("screenX")->getConst<Float>();
    ctx.y = get("screenY")->getConst<Float>();
    ctx.width = get("width")->getConst<Float>();
    ctx.height = get("height")->getConst<Float>();
}

void oA::Item::show(Uint indent, Log &log) const noexcept
{
    log << repeat(indent) << '\t' << "@" + getName() + "@:\t" << get("id")->toString() << endl;
    ++indent;
    _properties.apply([indent, &log](const auto &pair) {
        if (pair.first == "id")
            return;
        log << repeat(indent) << '\t' << "#" + pair.first + "#: " << pair.second->get().toString() << endl;
    });
    _childs.apply([indent, &log](const auto &child) {
        log << endl;
        child->show(indent, log);
    });
}

oA::Log &operator<<(oA::Log &log, const oA::Item &item)
{
    item.show(0, log);
    return (log);
}