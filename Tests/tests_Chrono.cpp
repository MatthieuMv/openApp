/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Chrono
*/

#include <criterion/criterion.h>
#include <thread>
#include "Core/Chrono.hpp"

Test(Chrono, Basics)
{
    oA::Chrono ch;

    ch.reset();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cr_assert_eq(ch.getSeconds(), 1);
}