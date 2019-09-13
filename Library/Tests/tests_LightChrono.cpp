/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_LightChrono
*/

#include <criterion/criterion.h>
#include <thread>
#include <openApp/Core/LightChrono.hpp>

Test(LightChrono, Basics)
{
    oA::LightChrono ch;
    oA::UInt s, ms, mc;

    ch.reset();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Micro first for better accuracy
    mc = ch.getMicroseconds(); ms = ch.getMilliseconds(); s = ch.getSeconds();
    cr_assert_eq(s, 1);
    cr_assert((ms % 1000) <= 1); // legit 1 ms delay max
    cr_assert((mc % 1000000) <= 1000); // same
}