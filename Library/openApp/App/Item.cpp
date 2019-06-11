/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#include <openApp/App/Item.hpp>

oA::Property<oA::Var> &oA::Item::append(const String &key)
{
    if (exists(key))
        throw LogicError("Item", "Can't append @" + key + "@, already exists");
    return *(_members[key] = std::make_shared<Expression<Var>>());
}

bool oA::Item::exists(const String &key)
{
    return _members.find(key) != _members.end();
}

oA::Property<oA::Var> &oA::Item::get(const String &key)
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

const oA::Property<oA::Var> &oA::Item::get(const String &key) const
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

void oA::Item::setExpression(const String &key, String expression)
{
    (void)(key);
    (void)(expression);
}

void oA::Item::addExpressionEvent(const String &key, String event)
{
    (void)(key);
    (void)(event);
}

oA::Item &oA::Item::appendChild(const ItemPtr &child)
{
    if (!child.get())
        throw LogicError("Item", "Can't append @null@ chill");
    return *_childs.emplace_back(std::move(child));
}

oA::Item &oA::Item::appendChild(ItemPtr &&child)
{
    if (!child.get())
        throw LogicError("Item", "Can't append @null@ chill");
    return *_childs.emplace_back(std::move(child));
}

bool oA::Item::existsChild(const String &id)
{
    return _childs.findIf([&id](const ItemPtr &child) {
        return id == child->getAs<Literal>("id");
    }) != _childs.end();
}

oA::Item &oA::Item::getChild(const String &id)
{
    auto it = _childs.findIf([&id](const ItemPtr &child) {
        return id == child->getAs<Literal>("id");
    });

    if (it == _childs.end())
        throw AccessError("Item", "Child with id @" + id + "@ doesn't exists");
    return *it->get();
}

const oA::Item &oA::Item::getChild(const String &id) const
{
    auto it = _childs.findIf([&id](const ItemPtr &child) {
        return id == child->getAs<Literal>("id");
    });

    if (it == _childs.end())
        throw AccessError("Item", "Child with id @" + id + "@ doesn't exists");
    return *it->get();
}