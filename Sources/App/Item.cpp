/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

// Item
#include "App/Item.hpp"

oA::Item &oA::Item::addChild(const ItemPtr &child)
{
    _childs.push_back(child);
    _childs.back()->_parent = this;
    return (*_childs.back());
}

oA::Item &oA::Item::addChild(ItemPtr &&child)
{
    _childs.emplace_back(std::move(child));
    return (*_childs.back());
}

void oA::Item::removeChild(const String &id)
{
    bool removed = false;

    _childs.removeIf([&id, &removed](const ItemPtr &child) {
        if (child->get("id")->getConst<String>() == id) {
            removed = true;
            return true;
        }
        return false;
    });
    if (!removed)
        throw AccessError("Item", "Couldn't find child with id @" + id + "@");
}

void oA::Item::removeChild(Uint idx)
{
    auto it = _childs.begin();

    if (idx >= childCount())
        throw AccessError("Item", "Child index out of range @" + oA::ToString(idx) + "@");
    std::advance(it, idx);
    _childs.erase(it);
}

oA::Uint oA::Item::childCount(void) const noexcept
{
    return _childs.size();
}

oA::Item &oA::Item::getChild(const String &id)
{
    auto it = _childs.findIf([&id](const ItemPtr &child) {
        return child->get("id")->getConst<String>() == id;
    });

    if (it == _childs.end())
        throw AccessError("Item", "Couldn't find child @" + id + "@");
    return (*it->get());
}

oA::Item &oA::Item::getChild(Uint idx)
{
    auto it = _childs.begin();

    if (_childs.size() <= idx)
        throw AccessError("Item", "Child index @" + ToString(idx) + "@ out of range");
    std::advance(it, idx);
    return (*it->get());
}

oA::ItemPtr oA::Item::getChildPtr(const String &id)
{
    auto it = _childs.findIf([&id](const ItemPtr &child) {
        return child->get("id")->getConst<String>() == id;
    });

    if (it != _childs.end())
        return *it;
    return oA::ItemPtr();
}

bool oA::Item::childExists(const String &id)
{
    auto it = _childs.findIf([&id](const ItemPtr &child) {
        return child->get("id")->getConst<String>() == id;
    });

    return it != _childs.end();
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