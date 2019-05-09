/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Path
*/

#include <criterion/criterion.h>
#include "Core/Path.hpp"

Test(Path, Exists)
{
    cr_assert(oA::Path::Exists("Makefile"));
    cr_assert(oA::Path::Exists("Includes"));
    cr_assert_not(oA::Path::Exists("abcdef"));
}

Test(Path, FileExists)
{
    cr_assert(oA::Path::FileExists("Makefile"));
    cr_assert_not(oA::Path::FileExists("Includes"));
    cr_assert_not(oA::Path::FileExists("abcdef"));
}

Test(Path, DirExists)
{
    cr_assert_not(oA::Path::DirExists("Makefile"));
    cr_assert(oA::Path::DirExists("Includes"));
    cr_assert_not(oA::Path::DirExists("abcdef"));
}