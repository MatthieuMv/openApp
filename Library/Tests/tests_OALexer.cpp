/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

#include <criterion/criterion.h>
#include <openApp/Language/Lexer.hpp>

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
    oA::Lang::OANode root;

    oA::Lang::Lexer::ProcessString(BasicFile, root);

    // Root
    cr_assert_eq(root.type, oA::Lang::OANode::RootNode);

    // Import
    cr_assert_eq(root.childs[0].type, oA::Lang::OANode::ImportNode);
    cr_assert_eq(root.childs[0].args[0], "Folder");

    // Item
    auto &item = root.childs[1];
    cr_assert_eq(item.type, oA::Lang::OANode::ItemNode);
    cr_assert_eq(item.args[0], "Item");

    // Property ID
    cr_assert_eq(item.childs[0].type, oA::Lang::OANode::AssignNode);
    cr_assert_eq(item.childs[0].args[0], "id");
    cr_assert_eq(item.childs[0].args[1], "myItem");

    // Property Empty
    cr_assert_eq(item.childs[1].type, oA::Lang::OANode::PropertyNode);
    cr_assert_eq(item.childs[1].args[0], "empty");
    cr_assert_eq(item.childs[1].args[1], "");

    // Property Life
    cr_assert_eq(item.childs[2].type, oA::Lang::OANode::PropertyNode);
    cr_assert_eq(item.childs[2].args[0], "life");
    cr_assert_eq(item.childs[2].args[1], "42");

    // Function ChangeLife
    cr_assert_eq(item.childs[3].type, oA::Lang::OANode::FunctionNode);
    cr_assert_eq(item.childs[3].args[0], "changeLife");
    cr_assert_eq(item.childs[3].args[1], "life");
    cr_assert_eq(item.childs[3].args[2], "=");
    cr_assert_eq(item.childs[3].args[3], "420");

    // Event on Life
    cr_assert_eq(item.childs[4].type, oA::Lang::OANode::EventNode);
    cr_assert_eq(item.childs[4].args[0], "life");
    cr_assert_eq(item.childs[4].args[1], "++x");
}

Test(Lexer, Errors)
{
    bool crashed = false;
    oA::Lang::OANode root;

    try { oA::Lang::Lexer::ProcessString("aze", root); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lang::Lexer::ProcessString("import", root); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lang::Lexer::ProcessString("Item {", root); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lang::Lexer::ProcessString("Item }", root); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lang::Lexer::ProcessString("property", root); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lang::Lexer::ProcessString("function", root); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { oA::Lang::Lexer::ProcessString("on", root); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}