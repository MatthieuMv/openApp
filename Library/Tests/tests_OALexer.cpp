/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OALexer
*/

#include <criterion/criterion.h>
#include <openApp/Language/OALexer.hpp>

static const auto BasicFile = \
"import Folder\n\
Item {\n\
    id:\tmyItem\n\
    property empty:  \n\
    property life:   42\n\
    function changeLife: {   life = 420 }\n\
    on life:\t\t++x\n\
}";

Test(OALexer, Basics)
{
    oA::OALexer::LexTree tree;

    oA::OALexer::ProcessString(BasicFile, tree);
    cr_assert_eq(tree.value.type, oA::OALexer::Root);

    auto &import = tree.children[0];
    cr_assert_eq(import.value.type, oA::OALexer::Import);
    cr_assert_eq(import.value.data[0], "Folder");

    auto &item = tree.children[1];
    cr_assert_eq(item.value.type, oA::OALexer::NewItem);
    cr_assert_eq(item.value.data[0], "Item");

    auto &id = item.children[0];
    cr_assert_eq(id.value.type, oA::OALexer::PropertyAssign);
    cr_assert_eq(id.value.data[0], "id");
    cr_assert_eq(id.value.data[1], "myItem");

    auto &empty = item.children[1];
    cr_assert_eq(empty.value.type, oA::OALexer::NewProperty);
    cr_assert_eq(empty.value.data[0], "empty");
    cr_assert_eq(empty.value.data[1], "");

    auto &property = item.children[2];
    cr_assert_eq(property.value.type, oA::OALexer::NewProperty);
    cr_assert_eq(property.value.data[0], "life");
    cr_assert_eq(property.value.data[1], "42");

    auto &function = item.children[3];
    cr_assert_eq(function.value.type, oA::OALexer::NewFunction);
    cr_assert_eq(function.value.data[0], "changeLife");
    cr_assert_eq(function.value.data[1], "life = 420");

    auto &event = item.children[4];
    cr_assert_eq(event.value.type, oA::OALexer::NewEvent);
    cr_assert_eq(event.value.data[0], "life");
    cr_assert_eq(event.value.data[1], "++x");
}

Test(OALexer, Errors)
{
    bool crashed = false;
    oA::OALexer::LexTree tree;

    try { oA::OALexer::ProcessString("aze", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::OALexer::ProcessString("import", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::OALexer::ProcessString("Item {", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::OALexer::ProcessString("Item }", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::OALexer::ProcessString("property", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::OALexer::ProcessString("function", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::OALexer::ProcessString("on", tree); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}