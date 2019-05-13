/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Log
*/

#define OA_NO_COLOR

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Core/Log.hpp"

Test(Log, Cout, .init=cr_redirect_stdout)
{
    oA::cout << 42 << oA::endl;
    cr_assert_stdout_eq_str("42\n");
}

Test(Log, Cerr, .init=cr_redirect_stderr)
{
    oA::cerr << 42 << oA::endl;
    cr_assert_stderr_eq_str("42\n");
}

Test(Log, Colors, .init=cr_redirect_stdout)
{
    auto res = oA::CSL_RED + "Red " + oA::CSL_GREEN + "Green" + oA::CSL_RESET + " " + oA::CSL_BLUE + "Blue" + oA::CSL_RESET + oA::CSL_RESET;
    oA::Log log(oA::Log::Stdout, oA::CSL_RED, oA::CSL_GREEN, oA::CSL_BLUE);

    log << "Red @Green@ #Blue#" << oA::endl;
}