/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ExpressionHandler
*/

#include <criterion/criterion.h>
#include <openApp/App/ExpressionHandler.hpp>

Test(ExpressionHandler, Basics)
{
    oA::ItemUtils::ExpressionHandler handler;
    const auto &ref(handler);

    cr_assert_not(handler.exists("a"));
    cr_assert_not(handler.exists("b"));
    handler.append("a") = "42";
    handler.append("b") = 42;
    cr_assert(handler.exists("a"));
    cr_assert(handler.exists("b"));

    cr_assert_eq(handler.get("a")->toInt(), 42);
    cr_assert_eq(handler.get("b")->toInt(), 42);

    cr_assert_eq(ref.get("a")->toInt(), 42);
    cr_assert_eq(ref.get("b")->toInt(), 42);

    cr_assert_eq(handler.getAs<oA::Literal>("a"), "42");
    cr_assert_eq(handler.getAs<oA::Number>("b"), 42);

    cr_assert_eq(handler.getPtr("a")->get().getAs<oA::Literal>(), "42");
    cr_assert_eq(handler.getPtr("b")->get().getAs<oA::Number>(), 42);
    cr_assert_eq(handler.getPtr("c").get(), nullptr);
}

Test(ExpressionHandler, Errors)
{
    oA::ItemUtils::ExpressionHandler handler;
    bool crashed = false;

    handler.append("a") = "42";
    try { handler.append("a"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.get("aze"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.getAs<oA::Literal>("aze"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
    try { handler.getAs<oA::Number>("a"); } catch (...) { crashed = true; }
    cr_assert(crashed); crashed = false;
}