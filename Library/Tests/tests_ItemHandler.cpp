/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Item
*/

#include <criterion/criterion.h>
#include <openApp/App/Item.hpp>

Test(ItemHandler, Basics)
{
    oA::ItemUtils::ItemHandler handler;
    const auto &ref(handler);

    cr_assert_eq(handler.childCount(), 0);
    handler.appendChild(std::make_shared<oA::Item>()).setID("item0");
    handler.appendChild(static_cast<const oA::ItemPtr &>(std::make_shared<oA::Item>())).setID("item1");
    handler.appendChild(std::make_shared<oA::Item>()).setID("item2");
    cr_assert_eq(handler.childCount(), 3);

    cr_assert(handler.childExists("item1"));
    cr_assert_eq(handler.getChild("item1").getID(), "item1");
    cr_assert_eq(ref.getChild("item1").getID(), "item1");

    handler.removeChild("item1");
    cr_assert_not(handler.childExists("item1"));
    cr_assert_eq(handler.childCount(), 2);

    handler.removeChild(0);
    cr_assert_eq(handler.childCount(), 1);
    cr_assert_eq(handler.getChild(0).getID(), "item2");
    cr_assert_eq(ref.getChild(0).getID(), "item2");
}

Test(ItemHandler, Errors)
{
    oA::ItemUtils::ItemHandler handler;
    const auto &ref(handler);
    bool crashed = false;
    oA::ItemPtr itm;

    try { handler.appendChild(nullptr); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.appendChild(itm); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.getChild(0); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.getChild("aze"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.removeChild(0); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.removeChild("aze"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref.getChild(0); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref.getChild("aze"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}