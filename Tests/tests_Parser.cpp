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

    cr_assert_eq(itm["id"]->getConst<oA::String>(), "myItem");
    cr_assert_eq(itm.childCount(), 1);
    cr_assert(itm.childExists("myChild"));
    auto &child = itm.getChild("myChild");
    cr_assert_eq(itm["x"]->toInt(), 50);
    cr_assert_eq(itm["y"]->toInt(), 50);
    cr_assert_eq(itm["width"]->toInt(), 200);
    cr_assert_eq(itm["height"]->toInt(), 100);
    cr_assert_eq(child["x"]->toInt(), 50);
    cr_assert_eq(child["y"]->toInt(), 25);
    cr_assert_eq(child["width"]->toInt(), 100);
    cr_assert_eq(child["height"]->toInt(), 50);
}

Test(Parser, Hard)
{
    auto ptr = oA::Parser::ParseFile("Resources/Hard.oA");
    cr_assert(ptr);
    auto &root = *ptr;

    cr_assert_eq(root["id"]->getConst<oA::String>(), "root");
    cr_assert_eq(root.childCount(), 1);
    cr_assert(root.childExists("child"));
    auto &child = root.getChild("child");
    cr_assert_eq(child.childCount(), 1);
    cr_assert(child.childExists("sub"));
    auto &sub = child.getChild("sub");
    cr_assert_eq(root["mult"]->toInt(), 1);
    cr_assert_eq(root["x"]->toInt(), 0);
    cr_assert_eq(root["y"]->toInt(), 0);
    cr_assert_eq(root["width"]->toInt(), 100);
    cr_assert_eq(root["height"]->toInt(), 100);
    cr_assert_eq(child["x"]->toInt(), 0);
    cr_assert_eq(child["y"]->toInt(), 0);
    cr_assert_eq(child["width"]->toInt(), 100);
    cr_assert_eq(child["height"]->toInt(), 100);
    cr_assert_eq(sub["x"]->toInt(), 0);
    cr_assert_eq(sub["y"]->toInt(), 0);
    cr_assert_eq(sub["width"]->toInt(), 100);
    cr_assert_eq(sub["height"]->toInt(), 100);
    root["mult"] = 2;
    cr_assert_eq(root["x"]->toInt(), 0);
    cr_assert_eq(root["y"]->toInt(), 0);
    cr_assert_eq(root["width"]->toInt(), 200);
    cr_assert_eq(root["height"]->toInt(), 200);
    cr_assert_eq(child["x"]->toInt(), 0);
    cr_assert_eq(child["y"]->toInt(), 0);
    cr_assert_eq(child["width"]->toInt(), 200);
    cr_assert_eq(child["height"]->toInt(), 200);
    cr_assert_eq(sub["x"]->toInt(), 50);
    cr_assert_eq(sub["y"]->toInt(), 50);
    cr_assert_eq(sub["width"]->toInt(), 100);
    cr_assert_eq(sub["height"]->toInt(), 100);
}

Test(Parser, Ultimate)
{
    auto ptr = oA::Parser::ParseFile("Resources/Ultimate.oA");
    cr_assert(ptr);
    auto &wnd = *ptr;

    // Root item
    cr_assert_eq(wnd["id"]->getConst<oA::String>(), "wnd");
    cr_assert_eq(wnd.childCount(), 2);
    cr_assert(wnd.childExists("myWdg"));
    cr_assert(wnd.childExists("topDownItem"));
    cr_assert_eq(wnd["var"]->toInt(), 123);
    cr_assert_eq(wnd["width"]->toInt(), 1000);
    cr_assert_eq(wnd["height"]->toInt(), 500);
    cr_assert_eq(wnd["x"]->toInt(), 0);
    cr_assert_eq(wnd["y"]->toInt(), 0);
    // MyWidget
    auto &myWdg = wnd.getChild("myWdg");
    cr_assert_eq(myWdg.childCount(), 1);
    cr_assert(myWdg.childExists("btn"));
    auto &btn = myWdg.getChild("btn");
    cr_assert_eq(myWdg["var"]->toInt(), 123);
    cr_assert_eq(myWdg["width"]->toInt(), 1000 / 3);
    cr_assert_eq(myWdg["height"]->toInt(), 500 / 2);
    cr_assert_eq(myWdg["x"]->toInt(), static_cast<int>(1000.0 - (1000.0 / 3.0)));
    cr_assert_eq(myWdg["y"]->toInt(), 0);
    // topDown
    auto &topDownItem = wnd.getChild("topDownItem");
    cr_assert_eq(topDownItem.childCount(), 1);
    cr_assert(topDownItem.childExists("btn"));
    auto &btn2 = topDownItem.getChild("btn");
    cr_assert_eq(topDownItem["var"]->toInt(), 123);
    cr_assert_eq(topDownItem["width"]->toInt(), 100);
    cr_assert_eq(topDownItem["height"]->toInt(), 100);
    cr_assert_eq(topDownItem["x"]->toInt(), 0);
    cr_assert_eq(topDownItem["y"]->toInt(), 500 - 100);
    // btn
    cr_assert_eq(btn["var"]->toInt(), 123);
    cr_assert_eq(btn["padding"]->toInt(), 5);
    cr_assert_eq(btn2["source"]->toString(), "unpressed.img");
    cr_assert_not(btn["pressed"].get());
    cr_assert_eq(btn["width"]->toInt(), 323);
    cr_assert_eq(btn["height"]->toInt(), 240);
    cr_assert_eq(btn["x"]->toInt(), 5);
    cr_assert_eq(btn["y"]->toInt(), 5);
    // btn2
    cr_assert_eq(btn2["var"]->toInt(), 123);
    cr_assert_eq(btn2["padding"]->toInt(), 2);
    cr_assert_eq(btn2["source"]->toString(), "unpressed.img");
    cr_assert_not(btn2["pressed"].get());
    cr_assert_eq(btn2["width"]->toInt(), 100 - 4);
    cr_assert_eq(btn2["height"]->toInt(), 100 - 4);
    cr_assert_eq(btn2["x"]->toInt(), 2);
    cr_assert_eq(btn2["y"]->toInt(), 2);
}