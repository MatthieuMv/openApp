/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ContainerHelper
*/

#pragma once

#include <algorithm>
#include "Core/Function.hpp"

namespace oA
{
    template<typename Type, typename Value>
    class ContainerHelper : public Type
    {
    public:
        /* apply() : apply a const / non-const function to each element */
        void apply(const Function<void(Value &)> &fct) {
            for (auto it = Type::begin(); it != Type::end(); ++it)
                fct(*it);
        }

        void apply(const Function<void(const Value &)> &fct) {
            for (auto it = Type::begin(); it != Type::end(); ++it)
                fct(*it);
        }

        /* removeIf() : remove elements matching a value, or a predicate */
        void removeIf(const Value &valueToRemove) {
            auto it = std::remove_if(Type::begin(), Type::end(), valueToRemove);
            Type::erase(it, Type::end());
        }

        void removeIf(const Function<bool(const Value &)> &predicate) {
            auto it = std::remove_if(Type::begin(), Type::end(), predicate);
            Type::erase(it, Type::end());
        }
    };
}
