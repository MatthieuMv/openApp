/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Expression
*/

#include <criterion/criterion.h>
#include "Core/Expression.hpp"

Test(Expression, Basics)
{
    oA::Expression<int> expr;
    oA::PropertyPtr<int> p = oA::MakeShared<oA::Property<int>>(2);

    expr.addNode(1);
    expr.addNode(p);
    expr.addNode(oA::Expression<int>::Node(oA::Add));
    expr.compute();
    cr_assert_eq(expr.get(), 3);
    expr.clear();
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
    cr_assert(crashed);
    crashed = false;
    try {
        oA::Expression<int> expr;
        expr.addNode(1);
        expr.addNode(2);
        expr.addNode(oA::Expression<int>::Node(oA::LP));
        expr.compute();
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
    try {
        oA::Expression<int> expr;
        expr.addNode(oA::Expression<int>::Node(oA::Add));
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