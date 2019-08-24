/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Var
*/

#include <criterion/criterion.h>
#include <openApp/Core/Var.hpp>
#include <openApp/App/Item.hpp>

Test(Var, Basics)
{
    oA::Var empty,
            toCopy(42),
            toMove("24"),
            copied(toCopy),
            moved(std::move(toMove));
    const oA::Var &ref(copied);

    cr_assert_not(empty);
    cr_assert_eq(copied.index(), oA::Var::VNumber);
    cr_assert_eq(copied.getAs<oA::Number>(), 42);
    cr_assert_eq(ref.getAs<oA::Number>(), 42);
    cr_assert_eq(moved.index(), oA::Var::VLiteral);
    cr_assert_eq(moved.getAs<oA::Literal>(), "24");
    moved = std::move(toCopy);
    cr_assert_eq(moved.index(), oA::Var::VNumber);
    cr_assert_eq(moved.getAs<oA::Number>(), 42);
    copied = empty;
}

Test(Var, Number)
{
    bool crashed = false;
    oA::Var v1(42), v2(2);
    const auto &ref(v1);

    cr_assert_eq(v1.toBool(), true);
    cr_assert_eq(v1.toInt(), 42);
    cr_assert_eq(v1.toUint(), 42);
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
    try { v1[0]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref[0]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1.len(); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}

Test(Var, Literal)
{
    bool crashed = false;
    oA::Var v1("4"), v2("2"), v3("aze");
    const auto &ref(v1);

    cr_assert_eq(v1.len().toInt(), 1);
    cr_assert_eq(v2.len().toInt(), 1);
    cr_assert_eq(v3.len().toInt(), 3);
    cr_assert_eq(v1.toBool(), true);
    cr_assert_eq(v1.toInt(), 4);
    cr_assert_eq(v1.toUint(), 4);
    cr_assert_eq(v3.toInt(), 0);
    cr_assert_eq(v3.toUint(), 0);
    cr_assert_eq(v1.toFloat(), 4.0f);
    cr_assert_eq(v3.toFloat(), 0.0f);
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
    try { v1[0]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref[0]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}

Test(Var, Container)
{
    bool crashed = false;
    oA::Container c = {
        false, 1, 2.5, "3"
    };
    oA::Var v1(c), v2(c);
    const auto &ref(v1);

    cr_assert_eq(v1.toBool(), true);
    cr_assert_eq(v1.toInt(), oA::Int());
    cr_assert_eq(v1.toUint(), oA::Uint());
    cr_assert_eq(v1.toFloat(), oA::Float());
    cr_assert_eq(v1.toString(), oA::String("[ 0, 1, 2.5, 3 ]"));
    cr_assert_eq(v1.operator bool(), true);
    cr_assert_eq(!v1, false);
    cr_assert_eq(v1 == v2, true);
    cr_assert_eq(v1 != v2, false);
    cr_assert_eq(v1[2].toFloat(), 2.5);
    cr_assert_eq(v1.len().toUint(), 4);
    v1 += 42;
    cr_assert_eq(v1.len().toUint(), 5);
    cr_assert_eq(v1[--v1.len()].toInt(), 42);
    v1 -= 0;
    cr_assert_eq(v1.len().toUint(), 4);
    cr_assert_eq(v1[0].toInt(), 1);
    cr_assert_eq(ref[0].toInt(), 1);
    cr_assert_eq(v1[--v1.len()].toInt(), 42);
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
    try { v1 + v2; } catch (...) { crashed = true; }
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
    try { v1 -= 42; } catch (...) { crashed = true; }
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
    try { v1[42]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { v1[v1]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref[42]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { ref[ref]; } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}