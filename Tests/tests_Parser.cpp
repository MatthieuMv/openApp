/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Parser
*/

#include <criterion/criterion.h>
#include "App/Parser.hpp"

Test(Parser, Easy)
{
    auto ptr = oA::Parser::ParseFile("Resources/Easy.oA");
    cr_assert(ptr);
    auto &itm = *ptr;

    cr_assert_eq(itm["id"]->getConst<oA::String>(), "easyItem");
}