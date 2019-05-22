/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemChilds
*/

// Item
#include "App/Item.hpp"

oA::Item &oA::Item::addChild(const ItemPtr &child)
{
    _childs.push_back(child);
    return setupChild(_childs.back());
}

oA::Item &oA::Item::addChild(ItemPtr &&child)
{
    _childs.emplace_back(std::move(child));
    return setupChild(_childs.back());
}

oA::Item &oA::Item::setupChild(ItemPtr &child)
{
    child->_parent = this;
    child->makeExpression("screenX", "parent.screenX + x");
    child->makeExpression("screenY", "parent.screenY + y");
    onChildAdded();
    return (*child);
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
    onChildRemoved();
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