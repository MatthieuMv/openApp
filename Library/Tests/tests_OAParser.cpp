/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Parser
*/

#include <criterion/criterion.h>
#include <openApp/Language/Parser.hpp>

Test(Parser, Basics)
{
    auto item(oA::Lang::Parser::ProcessFile("TestMedias/Test01.oA"));
    
    cr_assert(item);
    cr_assert_eq(item->getID(), "myItem");
    cr_assert_eq(item->getAs<oA::Number>("x"), 50);
    cr_assert_eq(item->getAs<oA::Number>("y"), 100);
    cr_assert_eq(item->getAs<oA::Number>("width"), 150);
    cr_assert_eq(item->getAs<oA::Number>("height"), 200);
}