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
    update(renderer);
    draw(renderer);
    for (auto &child : _childs) {
        child->render(renderer);
    }
}

bool oA::Item::propagate(Event &evt)
{
    if (!*get("visible"))
        return false;
    for (auto &child : _childs) {
        if (child->propagate(evt))
            return true;
    }
    return onEvent(evt);
}

bool oA::Item::contains(const V2f &pos) const noexcept
{
    auto screenX = get("screenX")->getConst<Float>(), screenY = get("screenY")->getConst<Float>();
    return (
        pos.x >= screenX && pos.x <= (screenX + get("width")->getConst<Float>()) &&
        pos.y >= screenY && pos.y <= (screenY + get("height")->getConst<Float>())
    );
}

void oA::Item::getItemContext(ItemContext &ctx) const
{
    ctx.pos.x = get("screenX")->getConst<Float>();
    ctx.pos.y = get("screenY")->getConst<Float>();
    ctx.size.x = get("width")->getConst<Float>();
    ctx.size.y = get("height")->getConst<Float>();
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