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
    cr_assert_eq(x.getRaw(), 42);
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

Test(Property, Bind)
{
    oA::Property<oA::Int> x(1), y(2);

    x.bind(y);
    cr_assert_eq(*x, 1);
    cr_assert_eq(*y, 2);
    y = 3;
    cr_assert_eq(*x, 3);
    cr_assert_eq(*y, 3);
}

Test(Property, CircularBind)
{
    oA::Property<oA::Int> x(1), y(2);

    x.circularBind(y);
    cr_assert_eq(*x, 1);
    cr_assert_eq(*y, 2);
    y = 3;
    cr_assert_eq(*x, 3);
    cr_assert_eq(*y, 3);
    y = 4;
    cr_assert_eq(*x, 4);
    cr_assert_eq(*y, 4);
}

Test(Property, Assignments)
{
    oA::Property<oA::Int> x, y(1);

    cr_assert_eq(*(x += 4), 4);
    cr_assert_eq(*(x += y), 5);
    y = 0;
    x = 4;
    cr_assert_eq(*(y -= 4), -4);
    cr_assert_eq(*(x -= y), 8);
    cr_assert_eq(*(x *= 2), 16);
    cr_assert_eq(*(x *= y), -64);
    cr_assert_eq(*(x /= y), 16);
    cr_assert_eq(*(x /= 4), 4);
    cr_assert_eq(*(x %= 5), 4);
    cr_assert_eq(*(x %= y), 0);
}