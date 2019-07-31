/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Path
*/

#include <filesystem>
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

Test(Path, Absolute)
{
    cr_assert_eq(oA::Path::GetAbsolutePath("run_tests"), std::filesystem::absolute("run_tests").c_str());
}

Test(Path, Canonical)
{
    cr_assert_eq(oA::Path::GetCanonicalPath("run_tests"), std::filesystem::canonical("run_tests").c_str());
}
