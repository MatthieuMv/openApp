/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Property
*/

#include <criterion/criterion.h>
#include <openApp/Core/Property.hpp>
#include <openApp/Types/Scalars.hpp>

Test(Propert, Basics)
{
    oA::Property<oA::Int> x;

    cr_assert(x.set(42));
    cr_assert_not(x.set(42));
}

Test(Property, Constructors)
{
    oA::Int value = 42;
    oA::Property<oA::Int>   def,
                            valCopy(value),
                            valMove(std::move(value)),
                            copy(valCopy),
                            move(std::move(valMove));

    cr_assert_eq(*def, 0);
    cr_assert_eq(*(copy.operator->()), 42);
    cr_assert_eq(move.get(), 42);
}

Test(Property, Assignment)
{
    oA::Int x = 12, y = 21;
    oA::Property<oA::Int> p1, p2;

    p1 = x;
    cr_assert_eq(*p1, 12);
    p2 = std::move(y);
    cr_assert_eq(*p2, 21);
    p1 = p2;
    cr_assert_eq(*p1, 21);
    p1 = p2;
    cr_assert_eq(*p1, 21);
}