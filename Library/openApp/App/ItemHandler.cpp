/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemHandler
*/

#include <openApp/App/ItemHandler.hpp>
#include <openApp/App/Item.hpp>

oA::Item &oA::ItemUtils::ItemHandler::appendChild(const ItemPtr &child)
{
    if (!child.get())
        throw LogicError("Item", "Can't append @null@ chill");
    auto &p = _children.emplace_back(child);
    onAppendChild(*p);
    return *p;
}

oA::Item &oA::ItemUtils::ItemHandler::appendChild(ItemPtr &&child)
{
    if (!child.get())
        throw LogicError("Item", "Can't append @null@ chill");
    auto &p = _children.emplace_back(std::move(child));
    onAppendChild(*p);
    return *p;
}

void oA::ItemUtils::ItemHandler::removeChild(Uint index)
{
    auto it = _children.begin();

    if (index >= _children.size())
        throw AccessError("Item", "Can't remove child with out of range index @" + ToString(index) + "@");
    std::advance(it, index);
    onRemoveChild(**it);
    _children.erase(it);
}

void oA::ItemUtils::ItemHandler::removeChild(const String &id)
{
    auto count = 0;

    _children.removeIf([this, &id, &count](ItemPtr &ptr) {
        if (id != ptr->getID())
            return false;
        onRemoveChild(*ptr);
        ++count;
        return true;
    });
    if (!count)
        throw AccessError("Item", "Couldn't remove any instance of children with id @" + id + "@");
}

bool oA::ItemUtils::ItemHandler::childExists(const String &id) const noexcept
{
    return _children.findIf([&id](const ItemPtr &child) {
        return id == child->getID();
    }) != _children.end();
}

oA::Item &oA::ItemUtils::ItemHandler::getChild(Uint index)
{
    auto it = _children.begin();

    if (index >= _children.size())
        throw AccessError("Item", "Can't get child with out of range index @" + ToString(index) + "@");
    std::advance(it, index);
    return *it->get();
}

const oA::Item &oA::ItemUtils::ItemHandler::getChild(Uint index) const
{
    auto it = _children.begin();

    if (index >= _children.size())
        throw AccessError("Item", "Can't get child with out of range index @" + ToString(index) + "@");
    std::advance(it, index);
    return *it->get();
}

oA::Item &oA::ItemUtils::ItemHandler::getChild(const String &id)
{
    auto it = _children.findIf([&id](const ItemPtr &child) {
        return id == child->getID();
    });

    if (it == _children.end())
        throw AccessError("Item", "Child with id @" + id + "@ doesn't exists");
    return *it->get();
}

const oA::Item &oA::ItemUtils::ItemHandler::getChild(const String &id) const
{
    auto it = _children.findIf([&id](const ItemPtr &child) {
        return id == child->getID();
    });

    if (it == _children.end())
        throw AccessError("Item", "Child with id @" + id + "@ doesn't exists");
    return *it->get();
}
