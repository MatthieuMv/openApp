/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#include "Core/Error.hpp"
#include "App/Item.hpp"

oA::Item &oA::Item::addChild(ItemPtr &&child)
{
    _childs.emplace_back(std::move(child));
    return *_childs.back();
}

void oA::Item::removeChild(const oA::String &id)
{
    _childs.removeIf([&id](const ItemPtr &child) {
        return child->get_id() == id;
    });
}

oA::Item &oA::Item::operator[](oA::Uint i)
{
    auto it = _childs.begin();
    if (i > size())
        throw AccessError("Item", "Index out of range");
    std::advance(it, i);
    return (*it->get());
}

oA::Item &oA::Item::operator[](oA::Uint i) const
{
    auto it = _childs.begin();

    if (i > size())
        throw AccessError("Item", "Index out of range");
    std::advance(it, i);
    return (*it->get());
}
