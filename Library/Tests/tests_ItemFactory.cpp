/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ItemFactory
*/

#include <criterion/criterion.h>
#include <openApp/App/ItemFactory.hpp>

struct Foo : public oA::Item
{
    virtual oA::String getName(void) const noexcept { return "Foo"; }
};

Test(ItemFactory, Basics)
{
    oA::ItemFactory::Register<Foo>();
    cr_assert(oA::ItemFactory::Exists("Foo"));
    oA::ItemFactory::RegisterBaseItems();
    oA::ItemFactory::RegisterBaseItems();
    cr_assert(oA::ItemFactory::Exists("Item"));
    auto item = oA::ItemFactory::Instanciate("Foo");
    cr_assert(dynamic_cast<Foo *>(item.get()));
    cr_assert_not(oA::ItemFactory::Instanciate("FooBar"));
}