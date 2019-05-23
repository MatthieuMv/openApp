/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Operators
*/

#include <criterion/criterion.h>
#include "Core/Operators.hpp"

Test(Operators, Exists)
{
    cr_assert(oA::OperatorExists("+"));
    cr_assert(oA::OperatorExists("-"));
    cr_assert(oA::OperatorExists("*"));
    cr_assert(oA::OperatorExists("/"));
    cr_assert(oA::OperatorExists("%"));
    cr_assert(oA::OperatorExists("!"));
    cr_assert(oA::OperatorExists("&&"));
    cr_assert(oA::OperatorExists("||"));
    cr_assert(oA::OperatorExists("=="));
    cr_assert(oA::OperatorExists("!="));
    cr_assert(oA::OperatorExists(">"));
    cr_assert(oA::OperatorExists(">="));
    cr_assert(oA::OperatorExists("<"));
    cr_assert(oA::OperatorExists("<="));
    cr_assert(oA::OperatorExists("?"));
    cr_assert(oA::OperatorExists(":"));
    cr_assert(oA::OperatorExists("("));
    cr_assert(oA::OperatorExists(")"));
    cr_assert_not(oA::OperatorExists("(("));
    cr_assert_not(oA::OperatorExists("=!"));
}

Test(Operators, GetOperator)
{
    bool crashed = false;

    cr_assert_eq(oA::GetOperator("+").type, oA::Addition);
    cr_assert_eq(oA::GetOperator("==").type, oA::Equal);
    try {
        oA::GetOperator("?:");
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
}

Test(Operators, FormatExpr)
{
    oA::String expr = "x+y *z==4?89 :(property*42)/3";

    oA::FormatExpression(expr);
    cr_assert_eq(expr, "x + y * z == 4 ? 89 : ( property * 42 ) / 3");
}

Test(Operators, FormatExpr2)
{
    oA::String expr = "1+2*3 >2 ?3 :";

    oA::FormatExpression(expr);
    cr_assert_eq(expr, "1 + 2 * 3 > 2 ? 3 :");
}

Test(Operators, GetOperatorString)
{
    cr_assert_eq(oA::GetOperatorString(oA::Addition), "+");
    cr_assert_eq(oA::GetOperatorString(oA::Modulo), "%");
    cr_assert_eq(oA::GetOperatorString(oA::LeftParenthesis), "(");
    cr_assert_eq(oA::GetOperatorString(oA::InferiorEqual), "<=");
    cr_assert_eq(oA::GetOperatorString(oA::If), "?");
    cr_assert_eq(oA::GetOperatorString(oA::Else), ":");
    cr_assert_eq(oA::GetOperatorString(oA::None), "");
}