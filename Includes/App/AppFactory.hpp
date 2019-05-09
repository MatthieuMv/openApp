/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** AppFactory
*/

#pragma once

// Factory
#include "Core/Factory.hpp"
// Item
#include "App/Item.hpp"

namespace oA { class AppFactory; }

class oA::AppFactory
{
public:
    template<typename ItemDerived>
    static void Register(void) {
        FactoryInstance.registerDerived<ItemDerived>(ItemDerived().getName());
    }

    static ItemPtr Instanciate(const String &name) {
        auto item = FactoryInstance.instanciate(name);
        if (!item)
            throw RuntimeError("AppFactory", "Couldn't instanciate item @" + name + "@");
        return ItemPtr(item);
    }

    static bool Exists(const String &name) {
        return FactoryInstance.exists(name);
    }

    static void RegisterBaseItems(void);

private:
    static Factory<String, Item> FactoryInstance;
};