/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ContainerHelper
*/

#include <criterion/criterion.h>
#include "Core/Scalar.hpp"
#include "Core/Vector.hpp"
#include "Core/List.hpp"

Test(ContainerHelper, VectorHelper)
{
    oA::Vector<oA::Int> v = { 1, 2, 3, 4, 5 };

    v.removeIf([](auto x) {
        return x < 3;
    });
    cr_assert_eq(v.size(), 3);
    v.removeIf(3);
    cr_assert_eq(v.size(), 2);
    v.removeIf([](auto x) {
        return x < 5;
    });
    cr_assert_eq(v.size(), 1);
    cr_assert_eq(v.front(), 5);
}

Test(ContainerHelper, ListHelper)
{
    oA::List<oA::Int> v = { 1, 2, 3, 4, 5 };

    v.removeIf([](auto x) {
        return x < 3;
    });
    cr_assert_eq(v.size(), 3);
    v.removeIf(3);
    cr_assert_eq(v.size(), 2);
    v.removeIf([](auto x) {
        return x < 5;
    });
    cr_assert_eq(v.size(), 1);
    cr_assert_eq(v.front(), 5);
}