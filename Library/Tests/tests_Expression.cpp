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
    oA::Shared<oA::Expression<oA::Int>> tmp(std::make_shared<oA::Expression<oA::Int>>(0));
    oA::Expression<oA::Int> expr;

    cr_assert_not(expr.compute());
    expr.addNode(tmp, true);
    expr.addNode(2);
    expr.addNode(oA::RPN::Multiplication);
    expr.call();
    cr_assert_eq(*expr, 0);
    cr_assert(tmp->set(2));
    cr_assert_eq(*expr, 4);
}