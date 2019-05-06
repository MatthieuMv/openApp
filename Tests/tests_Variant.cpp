/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Variant
*/

#include <criterion/criterion.h>
#include "Core/Error.hpp"
#include "App/Variant.hpp"

Test(Variant, Basics)
{
    oA::Variant var;
    bool invalidCall = false;

    var = 1.2f;
    cr_assert_eq(var.toFloat(), 1.2f);
    cr_assert_eq(var.toInt(), 1);
    try {
        var.toString();
    } catch (const oA::Error &e) {
        invalidCall = true;
    }
    cr_assert(invalidCall);
    var = oA::String("123");
    cr_assert_eq(var.toString(), "123");
}