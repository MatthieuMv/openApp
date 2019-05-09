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