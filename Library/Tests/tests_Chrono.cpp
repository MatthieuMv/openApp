/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Chrono
*/

#include <criterion/criterion.h>
#include <thread>
#include <openApp/Core/Chrono.hpp>

Test(Chrono, Basics)
{
    oA::Chrono ch;
    oA::Uint s, ms, mc;

    cr_assert_not(ch.isPaused());
    ch.reset();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ch.pause();
    cr_assert(ch.isPaused());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Micro first for better accuracy
    mc = ch.getMicroseconds(); ms = ch.getMilliseconds(); s = ch.getSeconds();
    ch.resume();
    cr_assert_not(ch.isPaused());
    cr_assert_eq(s, 1);
    cr_assert((ms % 1000) <= 1); // legit 1 ms delay max
    cr_assert((mc % 1000000) <= 1000); // same
}