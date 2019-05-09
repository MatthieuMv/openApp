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

void oA::Item::removeChild(const String &id)
{
    bool removed = false;

    _childs.removeIf([&id, &removed](const ItemPtr &child) {
        if (child->get("id")->get<String>() == id) {
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

oA::Property<oA::Variant> &oA::Item::append(const String &name)
{
    _properties[name] = std::make_shared<Expression<Variant>>();
    return (get(name));
}

void oA::Item::remove(const String &name)
{
    _properties.removeIf([&name](const auto &p) {
        return p.first == name;
    });
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

void oA::Item::show(Uint indent) const noexcept
{
    return showWith(indent, cout);
}

void oA::Item::showWith(Uint indent, Log &log) const noexcept
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
        child->showWith(indent, log);
    });
}

oA::Log &operator<<(oA::Log &log, const oA::Item &item)
{
    item.showWith(0, log);
    return (log);
}