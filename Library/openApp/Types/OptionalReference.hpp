/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OptionalReference
*/

#pragma once

namespace oA { template<typename T> class OptionalReference; }

/**
 * @brief Simple template class that allow returning a reference or an allocated value (can't be null)
 *
 * @tparam T Internal type
 */
template<typename T>
class oA::OptionalReference
{
public:
    OptionalReference(void) : _ref(new T()), _ownership(true) {}

    OptionalReference(T &value) : _ref(&value), _ownership(false) {}

    OptionalReference(OptionalReference &&other) : _ref(other._ref), _ownership(other._ownership) {
        other._ref = nullptr;
        other._ownership = false;
    }

    template<typename... Args>
    OptionalReference(Args &&...args) : _ref(new T(std::forward<Args>(args)...)), _ownership(true) {}

    ~OptionalReference(void) {
        if (_ownership)
            delete _ref;
    }

    bool hasOwnership(void) const noexcept { return _ownership; }

    T &operator*(void) { return *_ref; }
    const T &operator*(void) const { return *_ref; }

    T *operator->(void) { return _ref; }
    const T *operator->(void) const { return _ref; }

    OptionalReference<T> &operator=(OptionalReference<T> &&other) {
        if (_ownership)
            delete _ref;
        _ref = other._ref;
        _ownership = other._ownership;
        other._ref = nullptr;
        other._ownership = false;
        return *this;
    }

private:
    mutable T *_ref;
    bool _ownership;
};