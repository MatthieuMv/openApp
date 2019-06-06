/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** V2
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/Error.hpp>

namespace oA
{
    template<typename T> struct V2;

    using V2f = V2<Float>;
    using V2i = V2<Int>;
    using V2u = V2<Uint>;
}

/* Vector of 2, similar to a 2D point of type T */
template <typename T>
struct oA::V2
{
    V2(void) = default;
    V2(const V2<T> &other) : x(other.x), y(other.y) {}
    V2(const T X, const T Y) : x(X), y(Y) {}

    T x = T(), y = T();

    V2<T> &operator=(oA::V2<T> &&other) {
        x = other.x;
        y = other.y;
        return (*this);
    }

    V2<T> &operator=(const oA::V2<T> &other) {
        x = other.x;
        y = other.y;
        return (*this);
    }

    bool operator==(const oA::V2<T> &other) const noexcept {
        return x == other.x && y == other.y;
    }

    bool operator!=(const oA::V2<T> &other) const noexcept {
        return !(*this == other);
    }

    V2<T> &operator+=(const oA::V2<T> &other) {
        x += other.x;
        y += other.y;
        return (*this);
    }

    V2<T> &operator-=(const oA::V2<T> &other) {
        x -= other.x;
        y -= other.y;
        return (*this);
    }

    V2<T> &operator*=(const oA::V2<T> &other) {
        x *= other.x;
        y *= other.y;
        return (*this);
    }

    V2<T> &operator/=(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't divide by 0");
        x /= other.x;
        y /= other.y;
        return (*this);
    }

    V2<T> &operator%=(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't mod by 0");
        x %= other.x;
        y %= other.y;
        return (*this);
    }

    V2<T> operator+(const oA::V2<T> &other) {
        return oA::V2<T>(
            x + other.x,
            y + other.y
        );
    }

    V2<T> operator-(const oA::V2<T> &other) {
        return oA::V2<T>(
            x - other.x,
            y - other.y
        );
    }

    V2<T> operator*(const oA::V2<T> &other) {
        return oA::V2<T>(
            x * other.x,
            y * other.y
        );
    }

    V2<T> operator/(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't divide by 0");
        return oA::V2<T>(
            x / other.x,
            y / other.y
        );
    }

    V2<T> operator%(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't mod by 0");
        return oA::V2<T>(
            x % other.x,
            y % other.y
        );
    }
};