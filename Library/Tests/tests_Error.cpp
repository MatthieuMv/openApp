/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Errors
*/

#include <criterion/criterion.h>
#include "Core/Error.hpp"

Test(Error, Basics)
{
    oA::Error err("Name", "Data");

    cr_assert_str_eq(err.what(), "#Name:# Data");
}