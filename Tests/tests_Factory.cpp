/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Factory
*/

#include <criterion/criterion.h>
#include "Core/Factory.hpp"
#include "Core/Memory.hpp"

class Base { public: virtual ~Base(void) = default; };
class X : public Base {};
class Y : public Base {};

Test(Factory, Basics)
{
    oA::Factory<int, Base> f;

    cr_assert_not(f.exists(0));
    cr_assert_not(f.exists(1));
    f.registerDerived<X>(0);
    f.registerDerived<Y>(1);
    cr_assert(f.exists(0));
    cr_assert(f.exists(1));
    oA::Unique<Base> x(f.instanciate(0));
    oA::Unique<Base> y(f.instanciate(1));
    cr_assert(x);
    cr_assert(y);
    cr_assert(dynamic_cast<X *>(x.get()));
    cr_assert(dynamic_cast<Y *>(y.get()));
    cr_assert_not(f.instanciate(2));
}