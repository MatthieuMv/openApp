/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** V3
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/Error.hpp>

namespace oA
{
    template<typename T> struct V3;

    using V3f = V3<Float>;
    using V3i = V3<Int>;
    using V3u = V3<Uint>;
}

/* Vector of 2, similar to a 3D point of type T */
template <typename T>
struct oA::V3
{
    V3(void) = default;
    V3(const V3<T> &other) : x(other.x), y(other.y), z(other.z) {}
    V3(const T X, const T Y, const T Z) : x(X), y(Y), z(Z) {}

    T x = T(), y = T(), z = T();

    V3<T> &operator=(oA::V3<T> &&other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return (*this);
    }

    V3<T> &operator=(const oA::V3<T> &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return (*this);
    }

    bool operator==(const oA::V3<T> &other) const noexcept {
        return x == other.x && y == other.y && y == other.y && z == other.z;
    }

    bool operator!=(const oA::V3<T> &other) const noexcept {
        return !(*this == other);
    }

    V3<T> &operator+=(const oA::V3<T> &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return (*this);
    }

    V3<T> &operator-=(const oA::V3<T> &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return (*this);
    }

    V3<T> &operator*=(const oA::V3<T> &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return (*this);
    }

    V3<T> &operator/=(const oA::V3<T> &other) {
        if (!other.x || !other.y || !other.z)
            throw LogicError("V3", "Can't div by 0");
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return (*this);
    }

    V3<T> &operator%=(const oA::V3<T> &other) {
        if (!other.x || !other.y || !other.z)
            throw LogicError("V3", "Can't mod by 0");
        x %= other.x;
        y %= other.y;
        z %= other.z;
        return (*this);
    }

    V3<T> operator+(const oA::V3<T> &other) {
        return oA::V3<T>(
            x + other.x,
            y + other.y,
            z + other.z
        );
    }

    V3<T> operator-(const oA::V3<T> &other) {
        return oA::V3<T>(
            x - other.x,
            y - other.y,
            z - other.z
        );
    }

    V3<T> operator*(const oA::V3<T> &other) {
        return oA::V3<T>(
            x * other.x,
            y * other.y,
            z * other.z
        );
    }

    V3<T> operator/(const oA::V3<T> &other) {
        if (!other.x || !other.y || !other.z)
            throw LogicError("V3", "Can't div by 0");
        return oA::V3<T>(
            x / other.x,
            y / other.y,
            z / other.z
        );
    }

    V3<T> operator%(const oA::V3<T> &other) {
        if (!other.x || !other.y || !other.z)
            throw LogicError("V3", "Can't mod by 0");
        return oA::V3<T>(
            x % other.x,
            y % other.y,
            z % other.z
        );
    }
};