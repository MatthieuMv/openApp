/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Operator
*/

#include <criterion/criterion.h>
#include <openApp/Language/Operator.hpp>

Test(Operator, Basics)
{
    bool crashed = false;

    cr_assert(oA::Lang::IsOperator("+"));
    cr_assert_not(oA::Lang::IsOperator("-+"));
    cr_assert_eq(oA::Lang::GetOperator("+").type, oA::Lang::Addition);
    cr_assert_eq(oA::Lang::GetOperator(oA::Lang::Addition).type, oA::Lang::Addition);
    cr_assert_eq(oA::Lang::GetOperatorSymbol(oA::Lang::Addition), "+");
    cr_assert_eq(oA::Lang::GetOperatorSymbol(oA::Lang::Substraction), "-");

    try { oA::Lang::GetOperator("-+"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}