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
    bool crashed = false;
    oA::Item root;
    oA::ItemPtr item(std::make_shared<oA::Item>());
    const auto &ref(root);

    cr_assert_eq(item->getName(), "Item");
    item->get("id") = "item";
    cr_assert_eq(item->getAs<oA::Literal>("id"), "item");
    item->append("myVar") = 42;
    root.appendChild(item);
    root.appendChild(std::make_shared<oA::Item>()).get("id") = "child";
    cr_assert_eq(root.getChild("item").getAs<oA::Number>("myVar"), 42);
    cr_assert_eq(ref.getChild("item").getAs<oA::Number>("myVar"), 42);
    cr_assert(root.existsChild("child"));
    try { root.getChild("azerty"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref.getChild("azerty"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}

Test(Item, Expressions)
{
    oA::Item item;

    item.setExpression("id", "azerty");
    item.addExpressionEvent("id", "1 + 1");
}

Test(Item, Errors)
{
    oA::ItemPtr ptr;
    oA::Item item;
    const oA::Item &ref(item);
    bool crashed = false;

    item.appendChild(std::make_shared<oA::Item>());
    try { item.append("id"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { item.get("azerty"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref.get("azerty"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { item.appendChild(nullptr); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { item.appendChild(ptr); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}