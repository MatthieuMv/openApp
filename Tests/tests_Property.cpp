/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Property
*/

#include <criterion/criterion.h>
#include "Core/Property.hpp"

Test(Property, Basics)
{
    oA::Property<oA::Int> x(32), y(x), tmp, z(std::move(tmp));

    cr_assert_eq(x.get(), 32);
    cr_assert_eq(y.get(), 32);
    cr_assert_eq(z.get(), 0);
    x = 1;
    cr_assert_eq(x.get(), 1);
    x.set(12);
    cr_assert_eq(x.get(), 12);
    x = 0;
    x.connect([&x] { x.get() += 420; return true; });
    y.connect([&x] { x.emit(); return true; });
    y = 3;
    y = 3;
    cr_assert_eq(y.get(), 3);
    cr_assert_eq(x.get(), 420);
    z = std::move(y);
    z.emit();
    cr_assert_eq(x.get(), 840);
}