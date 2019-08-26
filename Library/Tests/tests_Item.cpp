/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Item
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <openApp/Items/Item.hpp>

Test(Item, Basics)
{
    oA::Item item;
    auto &child = item.appendChild(std::make_shared<oA::Item>());

    cr_assert_eq(item.getName(), "Item");
    item.setID("root");
    cr_assert_eq(item.getID(), "root");
    cr_assert_eq(child.getParent(), &item);
    child.setParent(nullptr);
    cr_assert_neq(child.getParent(), &item);
}

Test(Item, Expression)
{
    oA::Item item;

    item.setExpression("z", "y * 2");
    item.setFunction("fct", "height += 2");
    item.addExpressionEvent("z", "++width; fct();");
    cr_assert_eq(item.getAs<oA::Number>("z"), 0);
    cr_assert_eq(item.getAs<oA::Number>("width"), 0);
    cr_assert_eq(item.getAs<oA::Number>("height"), 0);
    item.get("y") = 1;
    cr_assert_eq(item.getAs<oA::Number>("z"), 2);
    cr_assert_eq(item.getAs<oA::Number>("width"), 1);
    cr_assert_eq(item.getAs<oA::Number>("height"), 2);
    item.get("y") = 2;
    cr_assert_eq(item.getAs<oA::Number>("z"), 4);
    cr_assert_eq(item.getAs<oA::Number>("width"), 2);
    cr_assert_eq(item.getAs<oA::Number>("height"), 4);
}

Test(Item, ExpressionItem)
{
    oA::Item root;
    auto &child = root.appendChild(std::make_shared<oA::Item>());
    auto &child2 = root.appendChild(std::make_shared<oA::Item>());
    auto &sub = child.appendChild(std::make_shared<oA::Item>());
    auto &sub2 = child2.appendChild(std::make_shared<oA::Item>());
    auto &last = sub2.appendChild(std::make_shared<oA::Item>());

    root.setID("root");
    child.setID("child");
    child2.setID("child2");
    sub.setID("sub");
    sub2.setID("sub2");
    last.setID("last");

    cr_assert_eq(last.findExpr("azerty").get(), nullptr);
    cr_assert_eq(last.findExpr("root.azerty").get(), nullptr);
    cr_assert_eq(last.findExpr("abc.azerty").get(), nullptr);

    cr_assert_eq(root.findExpr("root.x").get(), &root.get("x"));
    cr_assert_eq(root.findExpr("last.x").get(), &last.get("x"));
    cr_assert_eq(last.findExpr("root.x").get(), &root.get("x"));

    bool crashed = false;
    try { root.findExpr(".x"); }
    catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { root.findExpr("last."); }
    catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
}

Test(Item, FindItem)
{
    oA::Item root;
    auto &child = root.appendChild(std::make_shared<oA::Item>());
    auto &child2 = root.appendChild(std::make_shared<oA::Item>());
    auto &sub = child.appendChild(std::make_shared<oA::Item>());
    auto &sub2 = child2.appendChild(std::make_shared<oA::Item>());
    auto &last = sub2.appendChild(std::make_shared<oA::Item>());

    root.setID("root");
    child.setID("child");
    child2.setID("child2");
    sub.setID("sub");
    sub2.setID("sub2");
    last.setID("last");

    cr_assert_eq(root.findItem("aze"), nullptr);

    cr_assert_eq(root.findItem("parent"), nullptr);
    cr_assert_eq(root.findItem("root"), &root);
    cr_assert_eq(root.findItem("child"), &child);
    cr_assert_eq(root.findItem("child2"), &child2);
    cr_assert_eq(root.findItem("sub"), &sub);
    cr_assert_eq(root.findItem("sub2"), &sub2);
    cr_assert_eq(root.findItem("last"), &last);

    cr_assert_eq(child.findItem("parent"), &root);
    cr_assert_eq(child.findItem("root"), &root);
    cr_assert_eq(child.findItem("child"), &child);
    cr_assert_eq(child.findItem("child2"), &child2);
    cr_assert_eq(child.findItem("sub"), &sub);
    cr_assert_eq(child.findItem("sub2"), &sub2);
    cr_assert_eq(child.findItem("last"), &last);

    cr_assert_eq(child2.findItem("parent"), &root);
    cr_assert_eq(child2.findItem("root"), &root);
    cr_assert_eq(child2.findItem("child"), &child);
    cr_assert_eq(child2.findItem("child2"), &child2);
    cr_assert_eq(child2.findItem("sub"), &sub);
    cr_assert_eq(child2.findItem("sub2"), &sub2);
    cr_assert_eq(child2.findItem("last"), &last);

    cr_assert_eq(sub.findItem("parent"), &child);
    cr_assert_eq(sub.findItem("root"), &root);
    cr_assert_eq(sub.findItem("child"), &child);
    cr_assert_eq(sub.findItem("child2"), &child2);
    cr_assert_eq(sub.findItem("sub"), &sub);
    cr_assert_eq(sub.findItem("sub2"), &sub2);
    cr_assert_eq(sub.findItem("last"), &last);

    cr_assert_eq(sub2.findItem("parent"), &child2);
    cr_assert_eq(sub2.findItem("root"), &root);
    cr_assert_eq(sub2.findItem("child"), &child);
    cr_assert_eq(sub2.findItem("child2"), &child2);
    cr_assert_eq(sub2.findItem("sub"), &sub);
    cr_assert_eq(sub2.findItem("sub2"), &sub2);
    cr_assert_eq(sub2.findItem("last"), &last);
}

Test(Item, Show, .init=cr_redirect_stdout)
{
    oA::Item root;
    auto &child = root.appendChild(std::make_shared<oA::Item>());
    auto &child2 = root.appendChild(std::make_shared<oA::Item>());
    auto &sub = child.appendChild(std::make_shared<oA::Item>());
    auto &sub2 = child2.appendChild(std::make_shared<oA::Item>());
    auto &last = sub2.appendChild(std::make_shared<oA::Item>());

    root.setID("root");
    child.setID("child");
    child2.setID("child2");
    sub.setID("sub");
    sub2.setID("sub2");
    last.setID("last");
    root.show();
}