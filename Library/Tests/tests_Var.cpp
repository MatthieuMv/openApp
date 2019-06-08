/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Var
*/

#include <criterion/criterion.h>
#include <openApp/App/Var.hpp>
#include <openApp/App/Item.hpp>

Test(Var, Basics)
{
    oA::Var empty,
            toCopy(42),
            toMove("24"),
            copied(toCopy),
            moved(std::move(toMove));

    cr_assert_not(empty);
    cr_assert_eq(copied.index(), oA::Var::VNumber);
    cr_assert_eq(copied.get<oA::Var::Number>(), 42);
    cr_assert_eq(moved.index(), oA::Var::VLiteral);
    cr_assert_eq(moved.get<oA::Var::Literal>(), "24");
    moved = std::move(toCopy);
    cr_assert_eq(moved.index(), oA::Var::VNumber);
    cr_assert_eq(moved.get<oA::Var::Number>(), 42);
    copied = empty;
    cr_assert_not(copied);
}

Test(Var, Number)
{
    oA::Var v1(42), v2(2);

    cr_assert_eq(v1.toBool(), true);
    cr_assert_eq(v1.toInt(), 42);
    cr_assert_eq(v1.toFloat(), 42.0f);
    cr_assert_eq(v1.toString(), "42");
    cr_assert_eq(v1.operator bool(), true);
    cr_assert_eq(!v1, false);
    cr_assert_eq(v1 == v2, false);
    cr_assert_eq(v1 != v2, true);
    cr_assert_eq(v1 < v2, false);
    cr_assert_eq(v1 <= v2, false);
    cr_assert_eq(v1 > v2, true);
    cr_assert_eq(v1 >= v2, true);
    cr_assert_eq((v1 + v2).toInt(), 44);
    cr_assert_eq((v1 - v2).toInt(), 40);
    cr_assert_eq((v1 * v2).toInt(), 84);
    cr_assert_eq((v1 / v2).toInt(), 21);
    cr_assert_eq((v1 % v2).toInt(), 0);
    cr_assert_eq((v1 += v2).toInt(), 44);
    cr_assert_eq((v1 -= v2).toInt(), 42);
    cr_assert_eq((v1 *= v2).toInt(), 84);
    cr_assert_eq((v1 /= v2).toInt(), 42);
    cr_assert_eq((v1 %= v2).toInt(), 0);
    cr_assert_eq((v1++).toInt(), 0);
    cr_assert_eq((++v1).toInt(), 2);
    cr_assert_eq((v1--).toInt(), 2);
    cr_assert_eq((--v1).toInt(), 0);
}

Test(Var, Literal)
{
    bool crashed = false;
    oA::Var v1("4"), v2("2");

    cr_assert_eq(v1.toBool(), true);
    cr_assert_eq(v1.toInt(), 4);
    cr_assert_eq(v1.toFloat(), 4.0f);
    cr_assert_eq(v1.toString(), "4");
    cr_assert_eq(v1.operator bool(), true);
    cr_assert_eq(!v1, false);
    cr_assert_eq((v1 + v2).toInt(), 42);
    cr_assert_eq(v1 == v2, false);
    cr_assert_eq(v1 != v2, true);
    cr_assert_eq((v1 += v2).toString(), "42");
    try { v1 < v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 <= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 > v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 >= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 - v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 * v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 / v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 % v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 -= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 *= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 /= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 %= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1++; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ++v1; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1--; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { --v1; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}

Test(Var, Item)
{
    bool crashed = false;
    oA::ItemPtr item(std::make_shared<oA::Item>());
    oA::Var v1(item), v2(item);

    cr_assert_eq(v1.toBool(), true);
    cr_assert_eq(v1.operator bool(), true);
    cr_assert_eq(!v1, false);
    cr_assert_eq(v1 == v2, true);
    cr_assert_eq(v1 != v2, false);
    cr_assert_eq(v1.toInt(), oA::Int());
    cr_assert_eq(v1.toFloat(), oA::Float());
    cr_assert_eq(v1.toString(), oA::String());
    try { v1 + v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 < v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 <= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 > v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 >= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 - v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 * v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 / v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 % v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 += v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 -= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 *= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 /= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 %= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1++; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ++v1; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1--; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { --v1; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}

Test(Var, Container)
{
    bool crashed = false;
    oA::Var::Container c = {
        false, 1, 2.5, "3"
    };
    oA::Var v1(c), v2(c);

    cr_assert_eq(v1.toBool(), true);
    cr_assert_eq(v1.operator bool(), true);
    cr_assert_eq(!v1, false);
    cr_assert_eq(v1 == v2, true);
    cr_assert_eq(v1 != v2, false);
    cr_assert_eq(v1.toInt(), oA::Int());
    cr_assert_eq(v1.toFloat(), oA::Float());
    cr_assert_eq(v1.toString(), oA::String());
    try { v1 + v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 < v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 <= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 > v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 >= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 - v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 * v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 / v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 % v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 += v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 -= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 *= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 /= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1 %= v2; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1++; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ++v1; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1--; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { --v1; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}