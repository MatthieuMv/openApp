/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Item
*/

#include <criterion/criterion.h>
#include <openApp/App/Item.hpp>

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

Test(Item, FindItem)
{
    oA::Item root;
    auto &child = root.appendChild(std::make_shared<oA::Item>());
    auto &child2 = root.appendChild(std::make_shared<oA::Item>());
    auto &sub = child.appendChild(std::make_shared<oA::Item>());
    auto &sub2 = child2.appendChild(std::make_shared<oA::Item>());

    root.setID("root");
    child.setID("child");
    child2.setID("child2");
    sub.setID("sub");
    sub2.setID("sub2");

    cr_assert_eq(root.findItem("aze"), nullptr);

    cr_assert_eq(root.findItem("parent"), nullptr);
    cr_assert_eq(root.findItem("root"), &root);
    cr_assert_eq(root.findItem("child"), &child);
    cr_assert_eq(root.findItem("child2"), &child2);
    cr_assert_eq(root.findItem("sub"), &sub);
    cr_assert_eq(root.findItem("sub2"), &sub2);

    cr_assert_eq(child.findItem("parent"), &root);
    cr_assert_eq(child.findItem("root"), &root);
    cr_assert_eq(child.findItem("child"), &child);
    cr_assert_eq(child.findItem("child2"), &child2);
    cr_assert_eq(child.findItem("sub"), &sub);
    cr_assert_eq(child.findItem("sub2"), &sub2);

    cr_assert_eq(child2.findItem("parent"), &root);
    cr_assert_eq(child2.findItem("root"), &root);
    cr_assert_eq(child2.findItem("child"), &child);
    cr_assert_eq(child2.findItem("child2"), &child2);
    cr_assert_eq(child2.findItem("sub"), &sub);
    cr_assert_eq(child2.findItem("sub2"), &sub2);

    cr_assert_eq(sub.findItem("parent"), &child);
    cr_assert_eq(sub.findItem("root"), &root);
    cr_assert_eq(sub.findItem("child"), &child);
    cr_assert_eq(sub.findItem("child2"), &child2);
    cr_assert_eq(sub.findItem("sub"), &sub);
    cr_assert_eq(sub.findItem("sub2"), &sub2);

    cr_assert_eq(sub2.findItem("parent"), &child2);
    cr_assert_eq(sub2.findItem("root"), &root);
    cr_assert_eq(sub2.findItem("child"), &child);
    cr_assert_eq(sub2.findItem("child2"), &child2);
    cr_assert_eq(sub2.findItem("sub"), &sub);
    cr_assert_eq(sub2.findItem("sub2"), &sub2);
}
