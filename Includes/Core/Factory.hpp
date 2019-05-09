/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Factory
*/

#pragma once

// UMap
#include "Core/UMap.hpp"
// Function
#include "Core/Function.hpp"

namespace oA { template<typename Key, typename Base> class Factory; }

template<typename Key, typename Base>
class oA::Factory
{
public:
    using FactoryFunction = Function<Base*(void)>;

    template<typename Derived>
    void registerDerived(const Key &key) {
        _fcts[key] = [] {
            return dynamic_cast<Base *>(new Derived);
        };
    }

    Base *instanciate(const Key &key) {
        for (auto &pair : _fcts) {
            if (pair.first == key)
                return pair.second();
        }
        return nullptr;
    }

    bool exists(const Key &key) {
        for (const auto &pair : _fcts) {
            if (pair.first == key)
                return true;
        }
        return false;
    }

private:
    UMap<Key, FactoryFunction> _fcts;
};