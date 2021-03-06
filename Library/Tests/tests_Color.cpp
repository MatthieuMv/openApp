/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Color
*/

#include <criterion/criterion.h>
#include <openApp/Types/Color.hpp>

Test(Color, Basic)
{
    oA::Color c(255, 255, 255, 255), copy(c);

    cr_assert_eq(c.getA(), 255);
    cr_assert_eq(c.getR(), 255);
    cr_assert_eq(c.getG(), 255);
    cr_assert_eq(c.getB(), 255);
    cr_assert_eq(c.getValue(), 0xFFFFFFFF);
    cr_assert_eq(copy.getA(), 255);
    cr_assert_eq(copy.getR(), 255);
    cr_assert_eq(copy.getG(), 255);
    cr_assert_eq(copy.getB(), 255);
    cr_assert_eq(copy.getValue(), 0xFFFFFFFF);
    c.setTransparency(125);
    cr_assert_eq(c.getA(), 125);
    copy = c;
    cr_assert_eq(copy.getA(), 125);
}

Test(Color, Retreive)
{
    oA::Color c = oA::Color::RetreiveColor("red");
    bool crashed = false;

    cr_assert_eq(c.getA(), 255);
    cr_assert_eq(c.getR(), 255);
    cr_assert_eq(c.getG(), 0);
    cr_assert_eq(c.getB(), 0);
    try { c = oA::Color::RetreiveColor("aze"); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
}