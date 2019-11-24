/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemHandler
*/

#include <openApp/App/ItemHandler.hpp>
#include <openApp/Items/Item.hpp>

oA::Item &oA::ItemUtils::ItemHandler::appendChild(const ItemPtr &child)
{
    if (!child.get())
        throw LogicError("Item", "Can't append @null@ chill");
    if (childExists(child->getID()))
        throw LogicError("Item", "Can't append child @" + child->getID() + "@, a child already have this ID");
    auto &p = _children.emplace_back(child);
    onAppendChild(*p);
    onSizeChanged();
    return *p;
}

oA::Item &oA::ItemUtils::ItemHandler::appendChild(ItemPtr &&child)
{
    if (!child.get())
        throw LogicError("Item", "Can't append @null@ chill");
    if (childExists(child->getID()))
        throw LogicError("Item", "Can't append child @" + child->getID() + "@, a child already have this ID");
    auto &p = _children.emplace_back(std::move(child));
    onAppendChild(*p);
    onSizeChanged();
    return *p;
}

void oA::ItemUtils::ItemHandler::removeChild(UInt index)
{
    auto it = _children.begin();

    if (index >= _children.size())
        throw AccessError("Item", "Can't remove child with out of range index @" + ToString(index) + "@");
    std::advance(it, index);
    onRemoveChild(**it);
    _children.erase(it);
    onSizeChanged();
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
    onSizeChanged();
}

void oA::ItemUtils::ItemHandler::popChild(void)
{
    if (_children.empty())
        throw LogicError("Item", "Can't pop empty children list");
    onRemoveChild(*_children.back());
    _children.pop_back();
    onSizeChanged();
}

oA::ItemPtr oA::ItemUtils::ItemHandler::extractChild(UInt index)
{
    auto it = _children.begin();
    ItemPtr ptr;

    if (index >= _children.size())
        throw AccessError("Item", "Can't extract child with out of range index @" + ToString(index) + "@");
    std::advance(it, index);
    onRemoveChild(**it);
    ptr = *it;
    _children.erase(it);
    onSizeChanged();
    return ptr;
}

oA::ItemPtr oA::ItemUtils::ItemHandler::extractChild(const String &id)
{
    auto it = _children.findIf([&id](const auto &ptr) { return id == ptr->getID(); });
    ItemPtr ptr;

    if (it == _children.end())
        throw AccessError("Item", "Couldn't extract any instance of children with id @" + id + "@");
    ptr = *it;
    _children.erase(it);
    onSizeChanged();
    return ptr;
}

bool oA::ItemUtils::ItemHandler::childExists(const String &id) const noexcept
{
    return _children.findIf([&id](const ItemPtr &child) {
        return id == child->getID();
    }) != _children.end();
}

oA::Item &oA::ItemUtils::ItemHandler::getChild(UInt index)
{
    return *getChildPtr(index);
}

const oA::Item &oA::ItemUtils::ItemHandler::getChild(UInt index) const
{
    return *getChildPtr(index);
}

oA::Item &oA::ItemUtils::ItemHandler::getChild(const String &id)
{
    return *getChildPtr(id);
}

const oA::Item &oA::ItemUtils::ItemHandler::getChild(const String &id) const
{
    return *getChildPtr(id);
}

const oA::ItemPtr &oA::ItemUtils::ItemHandler::getChildPtr(UInt index) const
{
    auto it = _children.begin();

    if (index >= _children.size())
        throw AccessError("Item", "Can't get child with out of range index @" + ToString(index) + "@");
    std::advance(it, index);
    return *it;
}

const oA::ItemPtr &oA::ItemUtils::ItemHandler::getChildPtr(const String &id) const
{
    auto it = _children.findIf([&id](const ItemPtr &child) {
        return id == child->getID();
    });

    if (it == _children.end())
        throw AccessError("Item", "Child with id @" + id + "@ doesn't exists");
    return *it;
}