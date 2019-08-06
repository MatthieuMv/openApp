/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_StatementNode
*/

#include <criterion/criterion.h>
#include <openApp/Language/Nodes.hpp>

Test(StatementNode, If)
{
    oA::Lang::StatementNode node(oA::Lang::If);
    auto &condition = node.emplaceAs<oA::Lang::ValueNode>().value = 1;

    node.emplaceAs<oA::Lang::ValueNode>().value = 1;
    node.emplaceAs<oA::Lang::ValueNode>().value = 2;
    cr_assert_eq(node.compute(), oA::Var(1));
    condition = 0;
    cr_assert_eq(node.compute(), oA::Var(2));
}