/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ExpressionGroupNode
*/

#include <criterion/criterion.h>
#include <openApp/Language/Nodes.hpp>

Test(ExpressionGroupNode, Basics)
{
    oA::Lang::ExpressionGroupNode group;
    bool crashed = false;
    auto &child = group.emplaceAs<oA::Lang::StatementNode>(oA::Lang::Break);

    try { group.compute(); } catch (...) { crashed = true; }
    cr_assert(crashed);
    child.statement = oA::Lang::Return;
    child.emplaceAs<oA::Lang::ValueNode>(42);
    cr_assert_eq(group.compute().toInt(), 42);
}