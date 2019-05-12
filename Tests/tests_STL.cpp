/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_STL
*/

#include <criterion/criterion.h>
#include "Core.hpp"

Test(Pair, MakePair)
{
    auto pair = std::make_pair<int, int>(1, 2);
    auto pair2 = oA::MakePair<int, int>(1, 2);

    cr_assert_eq(pair, pair2);
}