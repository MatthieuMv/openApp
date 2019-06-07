/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ExpressionNode
*/

#include <criterion/criterion.h>
#include <openApp/Types/Scalars.hpp>
#include <openApp/Core/ExpressionNode.hpp>
#include <openApp/Core/Expression.hpp>

Test(ExpressionNode, Value)
{
    oA::ExpressionNode<oA::Int> node(12);
    bool crashed = false;

    cr_assert(node.isValue());
    cr_assert_not(node.isExpression());
    cr_assert_not(node.isOperator());
    try { node.getExpression(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { node.getOperator(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { cr_assert_eq(node.getValue(), 12); }
    catch (...) { crashed = true; }
    cr_assert_not(crashed);
    crashed = false;
}

Test(ExpressionNode, Operator)
{
    oA::ExpressionNode<oA::Int> node(oA::RPN::Addition);
    bool crashed = false;

    cr_assert_not(node.isValue());
    cr_assert_not(node.isExpression());
    cr_assert(node.isOperator());
    try { node.getExpression(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { cr_assert_eq(node.getOperator(), oA::RPN::Addition); }
    catch (...) { crashed = true; }
    cr_assert_not(crashed);
    crashed = false;
    try { node.getValue(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
}

Test(ExpressionNode, Expression)
{
    oA::ExpressionPtr<oA::Int> expr(new oA::Expression<oA::Int>(2));
    oA::ExpressionNode<oA::Int> node(expr);
    bool crashed = false;

    cr_assert(node.isValue());
    cr_assert(node.isExpression());
    cr_assert_not(node.isOperator());
    try { cr_assert_eq(node.getExpression()->get(), 2); }
    catch (...) { crashed = true; }
    cr_assert_not(crashed);
    crashed = false;
    try { node.getOperator(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { cr_assert_eq(node.getValue(), 2); }
    catch (...) { crashed = true; }
    cr_assert_not(crashed);
    crashed = false;
}