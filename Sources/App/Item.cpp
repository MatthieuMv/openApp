/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#include "App/Item.hpp"

oA::Item &oA::Item::addChild(ItemPtr &&child)
{
    _childs.emplace_back(std::move(child));
    return *_childs.back();
}

void oA::Item::removeChild(const oA::String &id)
{
    _childs.removeIf([&id](const ItemPtr &child) {
        return child->id() == id;
    });
}