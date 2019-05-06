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
    A Property is a simple way to implement Signal/Slot on any type.
    It acts like a custom getter / setter
*/
template<typename T>
class oA::Property : public oA::Signal<>
{
public:
    Property(void) {}

    T &get(void) noexcept { return _value; }
    const T &get(void) const noexcept { return _value; }

    bool set(const Property<T> &other) { return set(other.get()); }
    bool set(const T &value) {
        if (value == _value)
            return false;
        _value = value;
        emit();
        return true;
    }

    T &operator->(void) noexcept { return get(); }
    const T &operator->(void) const noexcept { return get(); }

    T &operator*(void) noexcept { return get(); }
    const T &operator*(void) const noexcept { return get(); }

    Property<T> &operator=(const Property<T> &other) { set(other.get()); return (*this); }
    Property<T> &operator=(const T &value) { set(value); return (*this); }

    template<typename U>
    void depends(Property<U> &other) noexcept {
        other.connect([this] {
            this->emit();
            return true;
        });
    }

private:
    T _value = T();
};