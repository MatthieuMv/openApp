/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Chrono
*/

#pragma once

// std::chrono
#include <chrono>

#include <openApp/Types/Scalars.hpp>

namespace oA { class Chrono; }

/**
 * @brief An easy and pausable time chronometer
 *
 */
class oA::Chrono
{
public:
    Chrono(void) : _chrono(std::chrono::system_clock::now()) {}

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

    /**
     * @brief Pause internal timer
     */
    void pause(void) noexcept {
        _paused = true;
        _pause = std::chrono::system_clock::now();
    }

    /**
     * @brief Resume internal timer
     */
    void resume(void) noexcept {
        auto cast = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now() - _pause
        );
        _chrono += cast;
        _paused = false;
    }

    /**
     * @brief Return pause internal state
     *
     * @return bool Pause state
     */
    bool isPaused(void) const noexcept {
        return _paused;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> _chrono, _pause;
    bool _paused = false;

    /**
     * @brief Get elapsed time, casting it to type T
     *
     * @tparam T Time interpretation type
     * @return UInt Elapsed time casted to T
     */
    template <typename T>
    UInt getAs(void) const noexcept {
        auto dt = _paused ? _pause : std::chrono::system_clock::now();
        return std::chrono::duration_cast<T>(
            dt - _chrono
        ).count();
    }
};