/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_GetLine
*/

#include <criterion/criterion.h>
#include <openApp/Core/GetLine.hpp>
#include <openApp/Types/SStream.hpp>

Test(GetLine, Basics)
{
    oA::String str = " \t\t hello world  \t ", target;
    oA::ISStream ss(str);

    cr_assert(oA::GetLine(ss, target));
    cr_assert_eq(target, "hello world");
    cr_assert_not(oA::GetLine(ss, target));
}