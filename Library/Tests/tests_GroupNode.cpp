/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ExpressionGroupNode
*/

#include <criterion/criterion.h>
#include <openApp/Language/Nodes.hpp>

Test(GroupNode, Basics)
{
    oA::Lang::GroupNode group;

    group.emplaceAs<oA::Lang::ValueNode>(42);
    cr_assert_eq(group.compute().toInt(), 42);
}