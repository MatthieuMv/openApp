/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Signal
*/

#pragma once

#include "Error.hpp"
#include "UMap.hpp"
#include "Function.hpp"

namespace oA
{
template<typename... Args>
class Signal
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
}