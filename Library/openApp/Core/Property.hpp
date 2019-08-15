/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Property
*/

#pragma once

#include <openApp/Core/Signal.hpp>

namespace oA { template<typename T> class Property; }

/**
 * @brief A lightweight signal / slot property variable
 *
 * Property class is used to create event on variables thank to Signal's base
 * It also allow (double) data binding thanks to a check secured setter
 *
 * @tparam T Internal Property type
 */
template<typename T>
class oA::Property : public Signal<>
{
public:
    /**
     * @brief Construct a new Property object
     */
    Property(void) = default;

    /**
     * @brief Destroy the Property object
     */
    virtual ~Property(void) = default;

    /**
     * @brief Construct a new Property object by value copy
     *
     * @param other Property to copy
     */
    Property(const T &value) : Signal<>(), _var(value) {}

    /**
     * @brief Construct a new Property object by value move
     *
     * @param other Property to move
     */
    Property(T &&value) : Signal<>(), _var(std::move(value)) {}

    /**
     * @brief Construct a new Property object by copy (will not copy Signal base)
     *
     * @param other Property to copy
     */
    Property(const Property<T> &other) : Signal<>(), _var(other._var) {}

    /**
     * @brief Construct a new Property object by move, swaping properties
     *
     * @param other Property to move
     */
    Property(Property<T> &&other) : Signal<>() { swap(other); }

    /**
     * @brief Boolean operator
     */
    operator bool(void) const noexcept { return _var; }

    /**
     * @brief Copy value assignment operator
     *
     * @param other Value to copy
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator=(const T &value) {
        set(value);
        return *this;
    }

    /**
     * @brief Move value assignment operator
     *
     * @param other Value to move
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator=(T &&value) {
        set(std::move(value));
        return *this;
    }

    /**
     * @brief Copy assignment operator
     *
     * @param other Value to copy
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator=(const Property<T> &other) {
        set(other.get());
        return *this;
    }

    /**
     * @brief Move assignment operator, swaping properties
     *
     * @param other Value to move
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator=(Property<T> &&other) {
        swap(other);
        return *this;
    }

    /**
     * @brief Addition value assignment operator
     *
     * @param other Value to add
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator+=(const T &value) {
        auto tmp = get();
        _var += value;
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Substraction value assignment operator
     *
     * @param other Value to sub
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator-=(const T &value) {
        auto tmp = get();
        _var -= value;
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Multiplication value assignment operator
     *
     * @param other Value to mult
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator*=(const T &value) {
        auto tmp = get();
        _var *= value;
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Division value assignment operator
     *
     * @param other Value to div
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator/=(const T &value) {
        auto tmp = get();
        _var /= value;
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Modulo value assignment operator
     *
     * @param other Value to mod
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator%=(const T &value) {
        _var %= value;
        this->emit();
        return *this;
    }

    /**
     * @brief Addition value assignment operator
     *
     * @param other Value to add
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator+=(const Property<T> &value) {
        auto tmp = get();
        _var += value.get();
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Substraction value assignment operator
     *
     * @param other Value to sub
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator-=(const Property<T> &value) {
        auto tmp = get();
        _var -= value.get();
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Multiplication value assignment operator
     *
     * @param other Value to mult
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator*=(const Property<T> &value) {
        auto tmp = get();
        _var *= value.get();
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Division value assignment operator
     *
     * @param other Value to div
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator/=(const Property<T> &value) {
        auto tmp = get();
        _var /= value.get();
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Modulo value assignment operator
     *
     * @param other Value to mod
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator%=(const Property<T> &value) {
        auto tmp = get();
        _var %= value.get();
        if (tmp != _var)
            this->emit();
        return *this;
    }

    /**
     * @brief Prefix increment operator
     *
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator++(void) {
        ++_var;
        this->emit();
        return *this;
    }

    /**
     * @brief Sufix increment operator
     *
     * @return Property<T>& Allow chain operators
     */
    Property<T> operator++(Int) {
        ++_var;
        this->emit();
        return _var - 1;
    }

    /**
     * @brief Prefix decrement operator
     *
     * @return Property<T>& Allow chain operators
     */
    Property<T> &operator--(void) {
        --_var;
        this->emit();
        return *this;
    }

    /**
     * @brief Sufix decrement operator
     *
     * @return Property<T>& Allow chain operators
     */
    Property<T> operator--(Int) {
        --_var;
        this->emit();
        return _var + 1;
    }

    /**
     * @brief Property reference getter operator
     *
     * @return const T& Const reference to internal value
     */
    const T &operator*(void) const noexcept { return get(); }

    /**
     * @brief Property pointer getter operator
     *
     * @return const T& Const pointer to internal value
     */
    const T *operator->(void) const noexcept { return &get(); }

    /**
     * @brief Property const getter
     *
     * @return const T& Const reference to internal value
     */
    const T &get(void) const noexcept { return _var; }

    /**
     * @brief Property getter (will not trigger emit on change !)
     *
     * @return const T& Reference to internal value
     */
    T &getRaw(void) noexcept { return _var; }

    /**
     * @brief Property copy setter
     *
     * @param value Value to copy
     * @return true Internal value changed
     * @return false Internal value didn't changed
     */
    bool set(const T &value) noexcept {
        if (_var == value)
            return false;
        _var = value;
        this->emit();
        return true;
    }

    /**
     * @brief Property move setter
     *
     * @param value Value to move
     * @return true Internal value changed
     * @return false Internal value didn't changed
     */
    bool set(T &&value) noexcept {
        if (_var == value)
            return false;
        _var = std::move(value);
        this->emit();
        return true;
    }

    /**
     * @brief Bind this's value to another Property
     *
     * This method provide a simple way to create data binding over properties
     *
     * @param other
     */
    void bind(Property<T> &other) noexcept {
        other.connect([&]{
            *this = other;
            return true;
        });
    }

    /**
     * @brief Bind this to another Property and another Property to this
     *
     * This method provide a simple way to create double data binding over properties
     *
     * @param other
     */
    void circularBind(Property<T> &other) noexcept {
        bind(other);
        other.bind(*this);
    }

    /**
     * @brief Swap two properties
     *
     * @param other Value to swap
     */
    void swap(Property<T> &other) {
        Signal::swap(other);
        std::swap(_var, other._var);
    }

private:
    T _var = T();
};