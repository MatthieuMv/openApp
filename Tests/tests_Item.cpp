/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Item
*/

#include <criterion/criterion.h>
#include "App/Item.hpp"

Test(Item, Properties)
{
    oA::Item itm;
    bool crashed = false;

    cr_assert_eq(itm.getName(), "Item");
    itm.append("z") = 42;
    cr_assert_eq(itm["z"]->toString(), "42");
    itm.remove("z");
    itm[oA::String("x")] = 4;
    try {
        const auto &x = itm;
        cr_assert_eq(x[oA::String("x")]->toInt(), 4);
        x["z"];
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
    try {
        itm["abc"] = 3;
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
}

Test(Item, Children)
{
    oA::Item itm;
    oA::ItemPtr tmp(new oA::Item);
    bool crashed = false;

    tmp->get("id") = "child";
    itm.addChild(oA::MakeShared<oA::Item>());
    cr_assert_eq(itm.childCount(), 1);
    itm.addChild(tmp);
    cr_assert_eq(itm.childCount(), 2);
    itm.removeChild("child");
    cr_assert_eq(itm.childCount(), 1);
    itm.removeChild(0);
    cr_assert_eq(itm.childCount(), 0);
    try {
        itm.removeChild("abc");
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
    try {
        itm.removeChild(4);
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
}

Test(Item, Expression1)
{
    oA::Item item;
    auto &child = item.addChild(oA::MakeShared<oA::Item>());

    child["id"] = "child";
    item.makeExpression("x", "child.width > 100 ? 42 : 420");
    cr_assert_eq(item["x"]->toInt(), 420);
    child["width"] = 101;
    cr_assert_eq(item["x"]->toInt(), 42);
}

Test(Item, Expression2)
{
    oA::Item item;

    item.makeExpression("x", "width > 100 ? 1 : (width <= 50 ? 2 : (width >= 75 ? 3 : 4))");
    item["width"] = 101;
    cr_assert_eq(item["x"]->toInt(), 1);
    item["width"] = 50;
    cr_assert_eq(item["x"]->toInt(), 2);
    item["width"] = 75;
    cr_assert_eq(item["x"]->toInt(), 3);
    item["width"] = 65;
    cr_assert_eq(item["x"]->toInt(), 4);
}

Test(Item, Find)
{
    oA::Item root;
    oA::Item &child = root.addChild(oA::MakeShared<oA::Item>());
    oA::Item &sub = child.addChild(oA::MakeShared<oA::Item>());

    root["id"] = "root";
    child["id"] = "child";
    sub["id"] = "sub";
    cr_assert_eq(root.find("child"), &child);
    cr_assert_eq(root.find("sub"), &sub);
    cr_assert_eq(child.find("root"), &root);
    cr_assert_eq(child.find("sub"), &sub);
    cr_assert_eq(sub.find("root"), &root);
    cr_assert_eq(sub.find("child"), &child);
}