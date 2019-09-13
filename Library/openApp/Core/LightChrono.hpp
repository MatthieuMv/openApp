/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** LightChrono
*/

#pragma once

// std::chrono
#include <chrono>

#include <openApp/Types/Scalars.hpp>

namespace oA { class LightChrono; }

/**
 * @brief A lightweight and easy to use time chronometer
 */
class oA::LightChrono
{
public:
    virtual ~LightChrono(void) = default;
    LightChrono(void) : _chrono(std::chrono::system_clock::now()) {}

    /**
     * @brief Get elapsed time in seconds
     *
     * @return UInt Seconds
     */
    UInt getSeconds(void) const noexcept { return getAs<std::chrono::seconds>(); }

    /**
     * @brief Get elapsed time in milliseconds
     *
     * @return UInt Milliseconds
     */
    UInt getMilliseconds(void) const noexcept { return getAs<std::chrono::milliseconds>(); }

    /**
     * @brief Get elapsed time in microseconds
     *
     * @return UInt Microseconds
     */
    UInt getMicroseconds(void) const noexcept { return getAs<std::chrono::microseconds>(); }

    /**
     * @brief Reset internal timer
     */
    void reset(void) noexcept {
        _chrono = std::chrono::system_clock::now();
    }

protected:
    std::chrono::time_point<std::chrono::system_clock> _chrono;

private:
    /**
     * @brief Get elapsed time, casting it to type T
     *
     * @tparam T Time interpretation type
     * @return UInt Elapsed time casted to T
     */
    template <typename T>
    UInt getAs(void) const noexcept {
        return std::chrono::duration_cast<T>(
            std::chrono::system_clock::now() - _chrono
        ).count();
    }
};