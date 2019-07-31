/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Lexer
*/

#include <criterion/criterion.h>
#include <openApp/Language/Lexer.hpp>

Test(Lexer, Basics)
{
    oA::Lang::Lexer::TokenList tokens;
    oA::Lang::Lexer::ProcessString("123-4*\n(++i)", tokens);
    auto it = tokens.begin();

    cr_assert_eq(it->first, "123"); cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "-");   cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "4");   cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "*");   cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "(");   cr_assert_eq(it->second, 2); ++it;
    cr_assert_eq(it->first, "++i"); cr_assert_eq(it->second, 2); ++it;
    cr_assert_eq(it->first, ")");   cr_assert_eq(it->second, 2);
}

Test(Lexer, Basics2)
{
    oA::Lang::Lexer::TokenList tokens;
    oA::Lang::Lexer::ProcessString("fct() container[4] property:", tokens);
    auto it = tokens.begin();

    cr_assert_eq(it->first, "fct");         cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "()");          cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "container");   cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "[]");           cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "4");           cr_assert_eq(it->second, 1); ++it;
    cr_assert_eq(it->first, "property:");   cr_assert_eq(it->second, 1); ++it;
}

// Test(Lexer, Basics3)
// {
//     oA::Lang::Lexer::TokenList tokens;
//     oA::Lang::Lexer::ProcessString("", tokens);
//     auto it = tokens.begin();

//     oA::Lang::Lexer::ShowTokenList(tokens);
// }