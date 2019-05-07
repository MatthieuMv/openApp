/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Error
*/

#include <criterion/criterion.h>
#include "Core/Error.hpp"

Test(Error, Basics)
{
    oA::Error err("Wtf"), err2("Section", "Wtf");

    cr_assert_str_eq(err.what(), "Wtf");
    cr_assert_str_eq(err2.what(), "#Section:# Wtf");
}