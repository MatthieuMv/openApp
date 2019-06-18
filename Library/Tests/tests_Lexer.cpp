/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Lexer
*/

#include <criterion/criterion.h>
#include <openApp/Language/Lexer.hpp>
#include <iostream>

static const auto BasicFile = \
"import Folder\n\
Item {\n\
    id:\tmyItem\n\
    property empty:  \n\
    property life:   42\n\
    function changeLife: {   life = 420 }\n\
    on life:\t\t++x\n\
}";

Test(Lexer, Basics)
{
    oA::Lexer::LexTree tree;

    oA::Lexer::ProcessString(BasicFile, tree);
    cr_assert_eq(tree.value.type, oA::Lexer::Root);

    auto &import = tree.childs[0];
    cr_assert_eq(import.value.type, oA::Lexer::Import);
    cr_assert_eq(import.value.data[0], "Folder");

    auto &item = tree.childs[1];
    cr_assert_eq(item.value.type, oA::Lexer::NewItem);
    cr_assert_eq(item.value.data[0], "Item");

    auto &id = item.childs[0];
    cr_assert_eq(id.value.type, oA::Lexer::PropertyAssign);
    cr_assert_eq(id.value.data[0], "id");
    std::cout << "Data1 = '" << id.value.data[1] << "'" << std::endl;
    cr_assert_eq(id.value.data[1], "myItem");

    auto &empty = item.childs[1];
    cr_assert_eq(empty.value.type, oA::Lexer::NewProperty);
    cr_assert_eq(empty.value.data[0], "empty");
    cr_assert_eq(empty.value.data[1], "");

    auto &property = item.childs[2];
    cr_assert_eq(property.value.type, oA::Lexer::NewProperty);
    cr_assert_eq(property.value.data[0], "life");
    cr_assert_eq(property.value.data[1], "42");

    auto &function = item.childs[3];
    cr_assert_eq(function.value.type, oA::Lexer::NewFunction);
    cr_assert_eq(function.value.data[0], "changeLife");
    cr_assert_eq(function.value.data[1], "life = 420");

    auto &event = item.childs[4];
    cr_assert_eq(event.value.type, oA::Lexer::NewEvent);
    cr_assert_eq(event.value.data[0], "life");
    cr_assert_eq(event.value.data[1], "++x");
}

Test(Lexer, Errors)
{
    bool crashed = false;
    oA::Lexer::LexTree tree;

    try { oA::Lexer::ProcessString("aze", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lexer::ProcessString("import", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lexer::ProcessString("Item {", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lexer::ProcessString("Item }", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lexer::ProcessString("property", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lexer::ProcessString("function", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lexer::ProcessString("on", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}