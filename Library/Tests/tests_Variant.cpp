/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Variant
*/

#include <criterion/criterion.h>
#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/Variant.hpp>

Test(Variant, Basics)
{
    oA::Variant<oA::Int, oA::Float> var;

    var = 3;
    cr_assert_eq(oA::Get<oA::Int>(var), 3);
    var = 3.5f;
    cr_assert_eq(oA::Get<oA::Float>(var), 3.5f);
}