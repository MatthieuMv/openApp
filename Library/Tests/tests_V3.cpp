/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_V3
*/

#include <criterion/criterion.h>
#include <openApp/Types/V3.hpp>

Test(V3, Basics)
{
    oA::V3i v1, v2(v1), v3(5, 5, 5);

    cr_assert(v1 == v2);
    v1.x = 1;
    cr_assert(v1 != v2);
    v1 = v3;
    cr_assert_eq(v1.x, 5);
    cr_assert_eq(v1.y, 5);
    cr_assert_eq(v1.z, 5);
    v2 = std::move(v3);
    cr_assert_eq(v2.x, 5);
    cr_assert_eq(v2.y, 5);
    cr_assert_eq(v2.z, 5);
}

Test(V3, OperatorsPlus)
{
    oA::V3i v1(2, 2, 2), v2(2, 2, 2), tmp;

    tmp += v1;
    cr_assert(tmp == v2);
    tmp = v1 + v2;
    cr_assert_eq(tmp.x, 4);
    cr_assert_eq(tmp.y, 4);
    cr_assert_eq(tmp.z, 4);
}

Test(V3, OperatorsLess)
{
    oA::V3i v1(2, 2, 2), v2(2, 2, 2), tmp;

    tmp -= v1;
    cr_assert_eq(tmp.x, -2);
    cr_assert_eq(tmp.y, -2);
    cr_assert_eq(tmp.z, -2);
    tmp = v1 - v2;
    cr_assert_eq(tmp.x, 0);
    cr_assert_eq(tmp.y, 0);
    cr_assert_eq(tmp.z, 0);
}

Test(V3, OperatorsMult)
{
    oA::V3i v1(2, 2, 2), v2(2, 2, 2), tmp;

    tmp *= v1;
    cr_assert_eq(tmp.x, 0);
    cr_assert_eq(tmp.y, 0);
    cr_assert_eq(tmp.z, 0);
    tmp = v1 * v2;
    cr_assert_eq(tmp.x, 4);
    cr_assert_eq(tmp.y, 4);
    cr_assert_eq(tmp.z, 4);
}

Test(V3, OperatorsDiv)
{
    oA::V3i v1(2, 2, 2), v2(2, 2, 2), tmp;
    bool crashed = false;

    try {
        v1 /= tmp;
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
    try {
        tmp = v1 / tmp;
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    tmp /= v1;
    cr_assert_eq(tmp.x, 0);
    cr_assert_eq(tmp.y, 0);
    cr_assert_eq(tmp.z, 0);
    tmp = v1 / v2;
    cr_assert_eq(tmp.x, 1);
    cr_assert_eq(tmp.y, 1);
    cr_assert_eq(tmp.z, 1);
}

Test(V3, OperatorsMod)
{
    oA::V3i v1(2, 2, 2), v2(3, 3, 3), tmp;
    bool crashed = false;

    try {
        v1 %= tmp;
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    crashed = false;
    try {
        tmp = v1 % tmp;
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
    tmp %= v1;
    cr_assert_eq(tmp.x, 0);
    cr_assert_eq(tmp.y, 0);
    cr_assert_eq(tmp.z, 0);
    tmp = v1 % v2;
    cr_assert_eq(tmp.x, 2);
    cr_assert_eq(tmp.y, 2);
    cr_assert_eq(tmp.z, 2);
}