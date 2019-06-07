/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Expression
*/

#include <criterion/criterion.h>
#include <openApp/Core/Expression.hpp>

Test(Expression, Basics)
{
    oA::ExpressionPtr<oA::Int> tmp(new oA::Expression<oA::Int>(0));
    oA::Expression<oA::Int> expr;

    cr_assert_not(expr.compute());
    expr.addNode(tmp, true);
    expr.addNode(tmp, true);
    expr.addNode(2);
    expr.addNode(oA::RPN::Multiplication);
    expr.addNode(oA::RPN::Addition);
    expr.call();
    cr_assert_eq(*expr, 0);
    cr_assert(tmp->set(1));
    cr_assert_eq(*expr, 3);
    expr.clearExpression();
    cr_assert(tmp->set(2));
    cr_assert_eq(*expr, 3);
}

Test(Expression, Advanced)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(2));
    oA::Expression<oA::Int> expr, evt;

    evt.addNode(ptr, false);
    evt.addNode(ptr, false);
    evt.addNode(2);
    evt.addNode(oA::RPN::Addition);
    evt.addNode(oA::RPN::Assign);
    expr.connectEvent(std::move(evt));
    cr_assert_eq(ptr->get(), 2);
    expr.call();
    cr_assert_eq(ptr->get(), 4);
    expr.clearSlots();
    expr.call();
    cr_assert_eq(ptr->get(), 4);
}

Test(Expression, Errors)
{
    bool crashed = false;

    try {
        oA::Expression<int> expr;
        expr.compute();
    } catch (...) {
        crashed = true;
    }
    cr_assert_not(crashed);
    crashed = false;
    try {
        oA::Expression<int> expr;
        expr.addNode(1);
        expr.addNode(2);
        expr.addNode(oA::RPN::LeftParenthesis);
        expr.compute();
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
    try {
        oA::Expression<int> expr;
        expr.addNode(oA::RPN::Addition);
        expr.compute();
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
    try {
        oA::Expression<int> expr;
        expr.addNode(1);
        expr.addNode(2);
        expr.compute();
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
}