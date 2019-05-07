/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Signal
*/

#pragma once

// Bool, Uint
#include "Core/Scalar.hpp"
// LogicError
#include "Core/Error.hpp"
// UMap
#include "Core/UMap.hpp"
// Function
#include "Core/Function.hpp"

namespace oA { template<typename... Args> class Signal; }

/*
    Signal is a simple way to implement signal slot on any type
*/
template<typename... Args>
class oA::Signal
{
public:
    using SignalFunction = Function<Bool(Args...)>;

    Uint connect(SignalFunction &&slot) noexcept {
        _slots.insert(std::make_pair(++_idx, std::move(slot)));
        return _idx;
    }

    void disconnect(Uint idx) {
        auto it = _slots.find(idx);
        if (it == _slots.end())
            throw LogicError("Signal", "Couldn't disconnect idx @" + std::to_string(idx) + "@");
        _slots.erase(it);
    }

    virtual void emit(Args ...args) {
        for (auto it = _slots.begin(); it != _slots.end();) {
            if (!it->second(args...))
                it = _slots.erase(it);
            else
                ++it;
        }
    }

private:
    UMap<Uint, SignalFunction> _slots;
    Uint _idx = 0;
};