/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_AppFactory
*/

#include <criterion/criterion.h>
#include "App/AppFactory.hpp"

class Derived : public oA::Item
{
public:
    virtual oA::String getName(void) const noexcept { return "Derived"; }
};

Test(AppFactory, Basics)
{
    cr_assert_not(oA::AppFactory::Exists("Derived"));
    oA::AppFactory::Register<Derived>();
    auto itm = oA::AppFactory::Instanciate("Derived");
    cr_assert(oA::AppFactory::Exists("Derived"));
    cr_assert(itm);
    cr_assert(dynamic_cast<Derived *>(itm.get()));
}

Test(AppFactory, Crash)
{
    bool crashed = false;

    try {
        oA::AppFactory::Instanciate("XYZ");
    } catch (...) {
        crashed = true;
    }
    cr_assert(crashed);
}