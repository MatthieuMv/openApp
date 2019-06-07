/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Expression
*/

#include <criterion/criterion.h>
#include <openApp/Types/Scalars.hpp>
#include <openApp/Core/ExpressionStack.hpp>
#include <openApp/Core/Expression.hpp>

Test(ExpressionStack, Basics)
{
    oA::ExpressionStack<oA::Int> stack;
    bool crashed = false;

    cr_assert_eq(stack.size(), 0);
    cr_assert(stack.empty());
    try { stack.pop(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { stack.top(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    stack.push(1);
    cr_assert_not(stack.empty());
    cr_assert_eq(stack.size(), 1);
}

Test(ExpressionStack, processAddition)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Addition);
    cr_assert_eq(expr.top().getValue(), 4);
}

Test(ExpressionStack, processSubstraction)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Substraction);
    cr_assert_eq(expr.top().getValue(), 0);
}

Test(ExpressionStack, processMultiplication)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Multiplication);
    cr_assert_eq(expr.top().getValue(), 4);
}

Test(ExpressionStack, processDivision)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Division);
    cr_assert_eq(expr.top().getValue(), 1);
}

Test(ExpressionStack, processModulo)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Modulo);
    cr_assert_eq(expr.top().getValue(), 0);
}

Test(ExpressionStack, processNot)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(0);
    expr.processOperator(oA::RPN::Not);
    cr_assert_eq(expr.top().getValue(), 1);
}

Test(ExpressionStack, processAnd)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::And);
    cr_assert_eq(expr.top().getValue(), 1);
}

Test(ExpressionStack, processOr)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(0);
    expr.push(2);
    expr.processOperator(oA::RPN::Or);
    cr_assert_eq(expr.top().getValue(), 1);
}

Test(ExpressionStack, processEqual)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Equal);
    cr_assert_eq(expr.top().getValue(), 1);
}

Test(ExpressionStack, processNotEqual)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Diff);
    cr_assert_eq(expr.top().getValue(), 0);
}

Test(ExpressionStack, processSuperior)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Superior);
    cr_assert_eq(expr.top().getValue(), 0);
}

Test(ExpressionStack, processSuperiorEqual)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::SuperiorEqual);
    cr_assert_eq(expr.top().getValue(), 1);
}

Test(ExpressionStack, processInferior)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::Inferior);
    cr_assert_eq(expr.top().getValue(), 0);
}

Test(ExpressionStack, processInferiorEqual)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(2);
    expr.processOperator(oA::RPN::InferiorEqual);
    cr_assert_eq(expr.top().getValue(), 1);
}

Test(ExpressionStack, processTernaryIf)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(1);
    expr.push(2);
    expr.push(3);
    expr.processOperator(oA::RPN::TernaryIf);
    cr_assert_eq(expr.top().getValue(), 2);
}

Test(ExpressionStack, processAssign)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(2));
    oA::ExpressionStack<oA::Int> expr;

    expr.push(ptr);
    expr.push(4);
    expr.processOperator(oA::RPN::Assign);
    cr_assert(expr.top().isExpression());
    cr_assert_eq(expr.top().getValue(), 4);
    cr_assert_eq(ptr->get(), 4);
}

Test(ExpressionStack, processAdditionAssign)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(2));
    oA::ExpressionStack<oA::Int> expr;

    expr.push(ptr);
    expr.push(4);
    expr.processOperator(oA::RPN::AdditionAssign);
    cr_assert(expr.top().isExpression());
    cr_assert_eq(expr.top().getValue(), 6);
    cr_assert_eq(ptr->get(), 6);
}

Test(ExpressionStack, processSubstractionAssign)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(2));
    oA::ExpressionStack<oA::Int> expr;

    expr.push(ptr);
    expr.push(4);
    expr.processOperator(oA::RPN::SubstractionAssign);
    cr_assert(expr.top().isExpression());
    cr_assert_eq(expr.top().getValue(), -2);
    cr_assert_eq(ptr->get(), -2);
}

Test(ExpressionStack, processMultiplicationAssign)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(2));
    oA::ExpressionStack<oA::Int> expr;

    expr.push(ptr);
    expr.push(4);
    expr.processOperator(oA::RPN::MultiplicationAssign);
    cr_assert(expr.top().isExpression());
    cr_assert_eq(expr.top().getValue(), 8);
    cr_assert_eq(ptr->get(), 8);
}

Test(ExpressionStack, processDivisionAssign)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(4));
    oA::ExpressionStack<oA::Int> expr;

    expr.push(ptr);
    expr.push(2);
    expr.processOperator(oA::RPN::DivisionAssign);
    cr_assert(expr.top().isExpression());
    cr_assert_eq(expr.top().getValue(), 2);
    cr_assert_eq(ptr->get(), 2);
}

Test(ExpressionStack, processModuloAssign)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(2));
    oA::ExpressionStack<oA::Int> expr;

    expr.push(ptr);
    expr.push(4);
    expr.processOperator(oA::RPN::ModuloAssign);
    cr_assert(expr.top().isExpression());
    cr_assert_eq(expr.top().getValue(), 2);
    cr_assert_eq(ptr->get(), 2);
}

Test(ExpressionStack, processCall)
{
    oA::ExpressionPtr<oA::Int> ptr(new oA::Expression<oA::Int>(2));
    bool ok = false;
    oA::ExpressionStack<oA::Int> expr;

    ptr->connect([&ok] { ok = true; return false; });
    expr.push(ptr);
    expr.processOperator(oA::RPN::Call);
    cr_assert(expr.top().isExpression());
    cr_assert_eq(expr.top().getValue(), 2);
    cr_assert_eq(ptr->get(), 2);
    cr_assert(ok);
}

Test(ExpressionStack, processSeparator)
{
    oA::ExpressionStack<oA::Int> expr;

    expr.push(2);
    expr.push(3);
    expr.processOperator(oA::RPN::Separator);
    cr_assert_eq(expr.size(), 1);
    cr_assert_eq(expr.top().getValue(), 3);
}