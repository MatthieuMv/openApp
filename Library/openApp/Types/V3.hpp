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
    using V3u = V3<UInt>;
}

/**
 * @brief Vector of 3, similar to a 3D point of type T
 *
 * @tparam T Type of the x, y and z values
 */
template <typename T>
struct oA::V3
{
    /**
     * @brief Construct a new V3 object with default values
     */
    V3(void) = default;

    /**
     * @brief Construct a new V3 object by copy
     *
     * @param other Value to copy
     */
    V3(const V3<T> &other) : x(other.x), y(other.y), z(other.z) {}

    /**
     * @brief Construct a new V3 object with x and y values
     *
     * @param X x value
     * @param Y y value
     * @param Z z value
     */
    V3(const T X, const T Y, const T Z) : x(X), y(Y), z(Z) {}

    T x = T(), y = T(), z = T();

    /**
     * @brief Move assignment operator
     *
     * @param other Value to move
     * @return V3<T>& Allow chain operators
     */
    V3<T> &operator=(oA::V3<T> &&other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return (*this);
    }

    /**
     * @brief Copy assignment operator
     *
     * @param other Value to copy
     * @return V3<T>& Allow chain operators
     */
    V3<T> &operator=(const oA::V3<T> &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return (*this);
    }

    /**
     * @brief Equal operator
     *
     * @param other Value to compare
     * @return true Equivalents
     * @reutrn false Not equivalents
     */
    bool operator==(const oA::V3<T> &other) const noexcept {
        return x == other.x && y == other.y && y == other.y && z == other.z;
    }

    /**
     * @brief Inequal operator
     *
     * @param other Value to compare
     * @return true Not equivalents
     * @reutrn false Equivalents
     */
    bool operator!=(const oA::V3<T> &other) const noexcept {
        return !(*this == other);
    }

    /**
     * @brief Addition assignement operator
     *
     * @param other Value to add
     * @return V3<T>& Allow chain operators
     */
    V3<T> &operator+=(const oA::V3<T> &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return (*this);
    }

    /**
     * @brief Substraction assignement operator
     *
     * @param other Value to substract
     * @return V3<T>& Allow chain operators
     */
    V3<T> &operator-=(const oA::V3<T> &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return (*this);
    }

    /**
     * @brief Multiplication assignement operator
     *
     * @param other Value to multiply
     * @return V3<T>& Allow chain operators
     */
    V3<T> &operator*=(const oA::V3<T> &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return (*this);
    }

    /**
     * @brief Addition assignement operator
     *
     * @param other Value to add
     * @return V3<T>& Allow chain operators
     */
    V3<T> &operator/=(const oA::V3<T> &other) {
        if (!other.x || !other.y || !other.z)
            throw LogicError("V3", "Can't div by 0");
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return (*this);
    }

    /**
     * @brief Modulo assignement operator
     *
     * @param other Value to mod
     * @return V3<T>& Allow chain operators
     */
    V3<T> &operator%=(const oA::V3<T> &other) {
        if (!other.x || !other.y || !other.z)
            throw LogicError("V3", "Can't mod by 0");
        x %= other.x;
        y %= other.y;
        z %= other.z;
        return (*this);
    }

    /**
     * @brief Addition operator
     *
     * @param other Value to add
     * @return V3<T> Result
     */
    V3<T> operator+(const oA::V3<T> &other) {
        return oA::V3<T>(
            x + other.x,
            y + other.y,
            z + other.z
        );
    }

    /**
     * @brief Substraction operator
     *
     * @param other Value to substract
     * @return V3<T> Result
     */
    V3<T> operator-(const oA::V3<T> &other) {
        return oA::V3<T>(
            x - other.x,
            y - other.y,
            z - other.z
        );
    }

    /**
     * @brief Multiplication operator
     *
     * @param other Value to multiply
     * @return V3<T> Result
     */
    V3<T> operator*(const oA::V3<T> &other) {
        return oA::V3<T>(
            x * other.x,
            y * other.y,
            z * other.z
        );
    }

    /**
     * @brief Division operator
     *
     * @param other Value to divide
     * @return V3<T> Result
     */
    V3<T> operator/(const oA::V3<T> &other) {
        if (!other.x || !other.y || !other.z)
            throw LogicError("V3", "Can't div by 0");
        return oA::V3<T>(
            x / other.x,
            y / other.y,
            z / other.z
        );
    }

    /**
     * @brief Modulo operator
     *
     * @param other Value to mod
     * @return V3<T> Result
     */
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