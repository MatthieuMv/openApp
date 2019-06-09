/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Item
*/

#include <criterion/criterion.h>
#include <openApp/App/Item.hpp>

#include <iostream>

Test(Item, Basics)
{
    oA::Item root;
    oA::ItemPtr item(std::make_shared<oA::Item>());

    item->get("id") = "item";
    cr_assert_eq(item->getAs<oA::Var::Literal>("id"), "item");
    item->append("myVar") = 42;
    root.appendChild(item);
    cr_assert_eq(root.getChild("item").getAs<oA::Var::Number>("myVar"), 42);
}

Test(Item, Errors)
{
    oA::Item item;
    bool crashed = false;

    try { item.append("id"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}