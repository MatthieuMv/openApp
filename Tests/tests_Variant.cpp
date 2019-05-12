/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Variant
*/

#include <criterion/criterion.h>
#include "Core/Error.hpp"
#include "Core/Variant.hpp"

Test(Variant, Basics)
{
    oA::Int x = 1;
    oA::Variant var(x);

    cr_assert_eq(var.index(), oA::VNumber);
    cr_assert_eq(var.get<oA::Float>(), 1.0f);
    cr_assert_eq(var.getConst<oA::Float>(), 1.0f);
    var = "Hello";
    cr_assert_eq(var.index(), oA::VString);
    cr_assert_eq(var.get<oA::String>(), "Hello");
    cr_assert_eq(var.getConst<oA::String>(), "Hello");
}

Test(Variant, Advanced)
{
    oA::Variant v1("1"), v2(2.0f);

    cr_assert_not(v1.isSameType(v2));
    cr_assert_eq(v1.toString(), "1");
    cr_assert_eq(v2.toString(), "2");
    v1 = v2;
    cr_assert(v1.isSameType(v2));
    cr_assert_eq(v1.toInt(), 2);
    v1 = 36;
    cr_assert_eq(v1.toFloat(), 36.0f);

}

Test(Variant, TypeConversion)
{
    oA::Variant var;
    bool invalidCall = false;

    var = 1.2f;
    cr_assert_eq(var.toFloat(), 1.2f);
    cr_assert_eq(var.toInt(), 1);
    try {
        var.get<oA::String>();
    } catch (const oA::Error &e) {
        invalidCall = true;
    }
    cr_assert(invalidCall);
    var = "123.5";
    invalidCall = false;
    try {
        var.get<oA::Float>();
    } catch (const oA::Error &e) {
        invalidCall = true;
    }
    cr_assert(invalidCall);
    cr_assert_eq(var.toString(), "123.5");
    cr_assert_eq(var.toFloat(), 123.5f);
    cr_assert_eq(var.toInt(), 123);
    var = "Hello";
    cr_assert_eq(var.toFloat(), 0.0f);
    cr_assert_eq(var.toInt(), 0);
}

Test(Variant, NumberOperators)
{
    oA::Variant x(3), y(4);

    cr_assert_eq((x + y).toInt(), 7);
    cr_assert_eq((x - y).toInt(), -1);
    cr_assert_eq((x * y).toInt(), 12);
    cr_assert_eq((x / y).toInt(), 0);
    cr_assert_eq((x % y).toInt(), 3);
    cr_assert_not(x == y);
    cr_assert(x != y);
    cr_assert_not(x > y);
    cr_assert_not(x >= y);
    cr_assert(x < y);
    cr_assert(x <= y);
    cr_assert(x && y);
    cr_assert(x || y);
    cr_assert(x);
    cr_assert_not(!x);
    cr_assert_eq((++x).toInt(), 4);
    cr_assert_eq((--x).toInt(), 3);
    cr_assert_eq((x += y).toInt(), 7);
    cr_assert_eq((x -= y).toInt(), 3);
    cr_assert_eq((x *= y).toInt(), 12);
    cr_assert_eq((x /= y).toInt(), 3);
    cr_assert_eq((x %= y).toInt(), 3);
}

Test(Variant, StringOperators)
{
    oA::Variant x("Hello"), y("World"), z;
    bool crashed = false;

    z = x;
    z += " ";
    z += y;
    cr_assert_eq((x + y).toString(), "HelloWorld");
    cr_assert_eq((z).toString(), "Hello World");
    cr_assert_not(x == y);
    cr_assert(x != y);
    cr_assert(x && y);
    cr_assert(x || y);
    cr_assert(x);
    cr_assert_not(!x);
    try { (x - y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x * y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x / y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x % y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x > y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x >= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x < y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x <= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (++x); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (--x); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x -= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x *= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x /= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x %= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
}

Test(Variant, CrossTypeOperators)
{
    oA::Variant x(12), y("World");

    cr_assert_not(x == y);
    cr_assert(x != y);
    cr_assert(x && y);
    cr_assert(x || y);
    cr_assert(x);
    cr_assert_not(!x);
}

Test(Variant, OperatorErrors)
{
    oA::Variant x(12), y("World");
    bool crashed = false;

    try { (x + y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x - y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x * y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x / y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x % y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x > y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x >= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x < y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { (x <= y); } catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
}