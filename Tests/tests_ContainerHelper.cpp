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
    v.apply([](const auto &x) {
        cr_assert_eq(x, 5);
    });
}

Test(ContainerHelper, ListApply)
{
    oA::List<oA::Int> v = { 0, 1, 2 };
    const oA::List<oA::Int> &constRef = v;

    v.apply([](oA::Int &x) {
        ++x;
    });
    auto it = v.begin();
    cr_assert_eq(*it, 1); ++it;
    cr_assert_eq(*it, 2); ++it;
    cr_assert_eq(*it, 3);
    v.apply([](oA::Int &x) {
        x = 5;
    });
    constRef.apply([](const oA::Int &x) {
        cr_assert_eq(x, 5);
    });
}

Test(ContainerHelper, FindIf)
{
    oA::List<oA::Int> v = { 0, 1, 2 };
    const oA::List<oA::Int> &constRef = v;

    auto it = v.findIf([](const auto &x) {
        return x == 0;
    });
    cr_assert_eq(it, v.begin());
    auto it2 = constRef.findIf([](const auto &x) {
        return x == 1;
    });
    cr_assert_eq(it2, ++constRef.begin());
    auto it3 = v.findIf([](const auto &x) {
        return x == 4;
    });
    cr_assert_eq(it3, v.end());
    auto it4 = constRef.findIf([](const auto &x) {
        return x == 4;
    });
    cr_assert_eq(it4, constRef.end());
}