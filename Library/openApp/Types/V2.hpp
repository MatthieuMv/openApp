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
    using V2u = V2<UInt>;
}

/**
 * @brief Vector of 2, similar to a 2D point of type T
 *
 * @tparam T Type of the x and y values
 */
template <typename T>
struct oA::V2
{
    /**
     * @brief Construct a new V2 object with default values
     */
    V2(void) = default;

    /**
     * @brief Construct a new V2 object by copy
     *
     * @param other Value to copy
     */
    V2(const V2<T> &other) : x(other.x), y(other.y) {}

    /**
     * @brief Construct a new V2 object with x and y values
     *
     * @param X x value
     * @param Y y value
     */
    V2(const T X, const T Y) : x(X), y(Y) {}

    T x = T(), y = T();

    /**
     * @brief Move assignment operator
     *
     * @param other Value to move
     * @return V2<T>& Allow chain operators
     */
    V2<T> &operator=(oA::V2<T> &&other) {
        x = other.x;
        y = other.y;
        return (*this);
    }

    /**
     * @brief Copy assignment operator
     *
     * @param other Value to copy
     * @return V2<T>& Allow chain operators
     */
    V2<T> &operator=(const oA::V2<T> &other) {
        x = other.x;
        y = other.y;
        return (*this);
    }

    /**
     * @brief Equal operator
     *
     * @param other Value to compare
     * @return true Equivalents
     * @reutrn false Not equivalents
     */
    bool operator==(const oA::V2<T> &other) const noexcept {
        return x == other.x && y == other.y;
    }

    /**
     * @brief Inequal operator
     *
     * @param other Value to compare
     * @return true Not equivalents
     * @reutrn false Equivalents
     */
    bool operator!=(const oA::V2<T> &other) const noexcept {
        return !(*this == other);
    }

    /**
     * @brief Addition assignement operator
     *
     * @param other Value to add
     * @return V2<T>& Allow chain operators
     */
    V2<T> &operator+=(const oA::V2<T> &other) {
        x += other.x;
        y += other.y;
        return (*this);
    }

    /**
     * @brief Substraction assignement operator
     *
     * @param other Value to substract
     * @return V2<T>& Allow chain operators
     */
    V2<T> &operator-=(const oA::V2<T> &other) {
        x -= other.x;
        y -= other.y;
        return (*this);
    }

    /**
     * @brief Multiplication assignement operator
     *
     * @param other Value to multiply
     * @return V2<T>& Allow chain operators
     */
    V2<T> &operator*=(const oA::V2<T> &other) {
        x *= other.x;
        y *= other.y;
        return (*this);
    }

    /**
     * @brief Addition assignement operator
     *
     * @param other Value to add
     * @return V2<T>& Allow chain operators
     */
    V2<T> &operator/=(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't divide by 0");
        x /= other.x;
        y /= other.y;
        return (*this);
    }

    /**
     * @brief Modulo assignement operator
     *
     * @param other Value to mod
     * @return V2<T>& Allow chain operators
     */
    V2<T> &operator%=(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't mod by 0");
        x %= other.x;
        y %= other.y;
        return (*this);
    }

    /**
     * @brief Addition operator
     *
     * @param other Value to add
     * @return V2<T> Result
     */
    V2<T> operator+(const oA::V2<T> &other) {
        return oA::V2<T>(
            x + other.x,
            y + other.y
        );
    }

    /**
     * @brief Substraction operator
     *
     * @param other Value to substract
     * @return V2<T> Result
     */
    V2<T> operator-(const oA::V2<T> &other) {
        return oA::V2<T>(
            x - other.x,
            y - other.y
        );
    }

    /**
     * @brief Multiplication operator
     *
     * @param other Value to multiply
     * @return V2<T> Result
     */
    V2<T> operator*(const oA::V2<T> &other) {
        return oA::V2<T>(
            x * other.x,
            y * other.y
        );
    }

    /**
     * @brief Division operator
     *
     * @param other Value to divide
     * @return V2<T> Result
     */
    V2<T> operator/(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't divide by 0");
        return oA::V2<T>(
            x / other.x,
            y / other.y
        );
    }

    /**
     * @brief Modulo operator
     *
     * @param other Value to mod
     * @return V2<T> Result
     */
    V2<T> operator%(const oA::V2<T> &other) {
        if (!other.x || !other.y)
            throw LogicError("V2", "Can't mod by 0");
        return oA::V2<T>(
            x % other.x,
            y % other.y
        );
    }
};