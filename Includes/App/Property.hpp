/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Property
*/

#pragma once

#include "Core/Signal.hpp"

namespace oA { template<typename T> class Property; }

/*
    A Property is a simple way of creating signal-handled variables
*/
template<typename T>
class oA::Property : public oA::Signal<>
{
public:
    Property(void) {}

    const T &get(void) const noexcept { return _value; }
    const T &operator*(void) const noexcept { return _value; }

    bool set(const Property<T> &other) { return set(other.get()); }
    bool set(const T &value) {
        if (value == _value)
            return false;
        _value = value;
        emit();
        return true;
    }

    template<typename U>
    void depends(Property<U> &other) noexcept {
        other.connect([this] {
            this->emit();
            return true;
        });
    }

    Property<T> &operator=(const Property<T> &other) { set(other.get()); return (*this); }
    Property<T> &operator=(const T &value) { set(value); return (*this); }

    const T &operator()(void) const noexcept { return get(); }
    bool operator()(const T &value) { return set(value); }

private:
    T _value = T();
};