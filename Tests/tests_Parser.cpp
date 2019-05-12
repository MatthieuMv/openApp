/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Parser
*/

#include <criterion/criterion.h>
#include "App/Parser.hpp"

Test(Parser, Easy)
{
    auto ptr = oA::Parser::ParseFile("Resources/Easy.oA");
    cr_assert(ptr);
    auto &itm = *ptr;

    cr_assert_eq(itm["id"]->getConst<oA::String>(), "easyItem");
    cr_assert_eq(itm.childCount(), 0);
}

Test(Parser, Medium)
{
    auto ptr = oA::Parser::ParseFile("Resources/Medium.oA");
    cr_assert(ptr);
    auto &itm = *ptr;

    oA::cout << itm;
    cr_assert_eq(itm["id"]->getConst<oA::String>(), "myItem");
    cr_assert_eq(itm.childCount(), 1);
    cr_assert(itm.childExists("myChild"));
    auto &child = itm.getChild("myChild");
    child.getExpr("x").show([](const auto &val) { return val.toString(); });
    cr_assert_eq(itm["x"]->toInt(), 50);
    cr_assert_eq(itm["y"]->toInt(), 50);
    cr_assert_eq(itm["width"]->toInt(), 200);
    cr_assert_eq(itm["height"]->toInt(), 100);
    cr_assert_eq(child["x"]->toInt(), 50);
    cr_assert_eq(child["y"]->toInt(), 25);
    cr_assert_eq(child["width"]->toInt(), 100);
    cr_assert_eq(child["height"]->toInt(), 50);
}