/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Property
*/

#pragma once

// Signal
#include "Core/Signal.hpp"
// Shared
#include "Core/Memory.hpp"

namespace oA { template<typename T> class Property; }

/*
    A Property is acts like a custom getter / setter and add signal slot to the variable
    ! Copying a Property will not copy its slots !
*/
template<typename T>
class oA::Property : public oA::Signal<>
{
public:
    Property(void) = default;
    Property(const T &value) : Signal<>(), _value(value) {}
    Property(T &&value) : Signal<>(), _value(value) {}
    Property(const Property<T> &other) : Signal<>(), _value(other._value) {}
    Property(Property<T> &&other) : Signal<>(), _value(other._value) {}

    T &get(void) noexcept { return _value; }
    const T &get(void) const noexcept { return _value; }

    bool set(const Property<T> &other) { return set(other.get()); }
    bool set(const T &value) {
        if (value == _value)
            return false;
        _value = value;
        this->emit();
        return true;
    }

    T &operator->(void) noexcept { return get(); }
    const T &operator->(void) const noexcept { return get(); }

    T &operator*(void) noexcept { return get(); }
    const T &operator*(void) const noexcept { return get(); }

    Property<T> &operator=(const Property<T> &other) { set(other.get()); return (*this); }
    Property<T> &operator=(Property<T> &&other) { _value = other._value; return (*this); }
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