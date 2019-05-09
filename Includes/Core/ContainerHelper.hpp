/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ContainerHelper
*/

#pragma once

// std::remove_if, std::find_if...
#include <algorithm>

// Function
#include "Core/Function.hpp"

namespace oA
{
    template<typename Type, typename Value>
    class ContainerHelper : public Type
    {
    public:
        using Type::Type;

        /* apply() : apply a const / non-const function to each element */
        void apply(const Function<void(Value &)> &fct) {
            for (auto it = Type::begin(); it != Type::end(); ++it)
                fct(*it);
        }

        void apply(const Function<void(const Value &)> &fct) const {
            for (auto it = Type::begin(); it != Type::end(); ++it)
                fct(*it);
        }

        /* removeIf() : remove elements matching a value, or a predicate */
        void removeIf(const Value &valueToRemove) {
            for (auto it = Type::begin(); it != Type::end();) {
                if (*it == valueToRemove)
                    it = Type::erase(it);
                else
                    ++it;
            }
        }

        void removeIf(const Function<bool(const Value &)> &predicate) {
            for (auto it = Type::begin(); it != Type::end();) {
                if (predicate(*it))
                    it = Type::erase(it);
                else
                    ++it;
            }
        }
    };
}
