/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

// AccessError
#include "Core/Error.hpp"

// Item
#include "App/Item.hpp"

oA::Item &oA::Item::addChild(const ItemPtr &child)
{
    _childs.push_back(child);
    return (*_childs.back());
}

oA::Item &oA::Item::addChild(ItemPtr &&child)
{
    _childs.emplace_back(std::move(child));
    return (*_childs.back());
}

void oA::Item::removeChild(const oA::String &id)
{
    _childs.removeIf([&id](const ItemPtr &child) {
        return child->get("id").get().toString() == id;
    });
}

oA::Uint oA::Item::childCount(void) const noexcept
{
    return _childs.size();
}

oA::Property<oA::Variant> &oA::Item::append(const oA::String &name)
{
    _properties.emplace(std::make_pair(name, Property<Variant>()));
    return ((*this)[name]);
}

void oA::Item::remove(const oA::String &name)
{
    _properties.removeIf([&name](const auto &p) {
        return p.first == name;
    });
}

oA::Property<oA::Variant> &oA::Item::get(const oA::String &name)
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        throw AccessError("Item", "Couldn't find property @" + name + "@");
    return (it->second);
}

const oA::Property<oA::Variant> &oA::Item::get(const oA::String &name) const
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        throw AccessError("Item", "Couldn't find property @" + name + "@");
    return (it->second);
}

oA::Property<oA::Variant> &oA::Item::operator[](const oA::String &name)
{
    return (get(name));
}

const oA::Property<oA::Variant> &oA::Item::operator[](const oA::String &name) const
{
    return (get(name));
}

oA::Property<oA::Variant> &oA::Item::operator[](const char *name)
{
    return this->operator[](String(name));
}

const oA::Property<oA::Variant> &oA::Item::operator[](const char *name) const
{
    return this->operator[](String(name));
}