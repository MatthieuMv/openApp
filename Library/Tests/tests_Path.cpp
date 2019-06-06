/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Path
*/

#include <criterion/criterion.h>
#include <openApp/Core/Path.hpp>

Test(Path, Exists)
{
    cr_assert(oA::Path::Exists("run_tests"));
    cr_assert_not(oA::Path::Exists("abcdef"));
}

Test(Path, FileExists)
{
    cr_assert(oA::Path::FileExists("run_tests"));
    cr_assert_not(oA::Path::FileExists("abcdef"));
}

Test(Path, DirExists)
{
    cr_assert(oA::Path::DirExists("../Library"));
    cr_assert_not(oA::Path::DirExists("abcdef"));
}