/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemProperty
*/

// Item
#include "App/Item.hpp"

oA::Property<oA::Variant> &oA::Item::append(const String &name)
{
    if (exists(name))
        throw LogicError("Item", "Can't append @" + name + "@, property already exists");
    _properties[name] = MakeShared<Expression<Variant>>();
    return (get(name));
}

void oA::Item::remove(const String &name)
{
    _properties.removeIf([&name](const auto &p) {
        return p.first == name;
    });
}

bool oA::Item::exists(const String &name)
{
    return _properties.find(name) != _properties.end();
}

oA::Property<oA::Variant> &oA::Item::get(const String &name)
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        throw AccessError("Item", "Couldn't find property @" + name + "@");
    return (*it->second);
}

const oA::Property<oA::Variant> &oA::Item::get(const String &name) const
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        throw AccessError("Item", "Couldn't find property @" + name + "@");
    return (*it->second);
}

oA::PropertyPtr<oA::Variant> oA::Item::getPtr(const String &name)
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        return PropertyPtr<Variant>();
    return (it->second);
}

oA::Property<oA::Variant> &oA::Item::operator[](const String &name)
{
    return (get(name));
}

const oA::Property<oA::Variant> &oA::Item::operator[](const String &name) const
{
    return (get(name));
}

oA::Property<oA::Variant> &oA::Item::operator[](const Char *name)
{
    return (get(name));
}

const oA::Property<oA::Variant> &oA::Item::operator[](const Char *name) const
{
    return (get(name));
}
