/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Statement
*/

#include <criterion/criterion.h>
#include <openApp/Language/Statement.hpp>

Test(Statement, Basics)
{
    bool crashed = false;

    cr_assert(oA::Lang::IsStatement("if"));
    cr_assert_not(oA::Lang::IsStatement("iff"));
    cr_assert_eq(oA::Lang::GetStatement("if").type, oA::Lang::If);
    cr_assert_eq(oA::Lang::GetStatement(oA::Lang::If).type, oA::Lang::If);
    cr_assert_eq(oA::Lang::GetStatementSymbol(oA::Lang::If), "if");
    cr_assert_eq(oA::Lang::GetStatementSymbol(oA::Lang::Switch), "switch");

    try { oA::Lang::GetStatement("+"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}