/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Signal
*/

#include <criterion/criterion.h>
#include "Core/Signal.hpp"

Test(Signal, Basics)
{
    oA::Int x = 42;
    oA::Signal<oA::Int &> sig;

    sig.connect([](oA::Int &x) {
        x *= 10;
        return false;
    });
    sig.emit(x);
    cr_assert_eq(x, 420);
}

Test(Signal, Connexion)
{
    oA::Int x = 0;
    oA::Signal<oA::Int &> sig;
    auto idx = sig.connect([](auto &x) { ++x; return true; });
    bool error = false;

    sig.emit(x);
    cr_assert_eq(x, 1);
    sig.disconnect(idx);
    sig.emit(x);
    cr_assert_eq(x, 1);
    try {
        sig.disconnect(idx);
    } catch (...) {
        error = true;
    }
    cr_assert(error);
}

Test(Signal, Copy)
{
    oA::Int x = 0;
    oA::Signal<oA::Int &> sig, cpy;
    auto idx = sig.connect([](auto &x) { ++x; return true; });

    cpy = sig;
    sig.emit(x);
    cr_assert_eq(x, 1);
    cpy.emit(x);
    cr_assert_eq(x, 2);
    sig.disconnect(idx);
    cpy.emit(x);
    cr_assert_eq(x, 3);
    cpy.disconnect(idx);
    cpy.emit(x);
    cr_assert_eq(x, 3);
}