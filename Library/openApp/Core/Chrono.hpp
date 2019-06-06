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

class oA::Chrono
{
public:
    Chrono(void) : _chrono(std::chrono::system_clock::now()) {}

    Uint getSeconds(void) const noexcept { return getAs<std::chrono::seconds>(); }
    Uint getMilliseconds(void) const noexcept { return getAs<std::chrono::milliseconds>(); }
    Uint getMicroseconds(void) const noexcept { return getAs<std::chrono::microseconds>(); }

    void reset(void) noexcept {
        _chrono = std::chrono::system_clock::now();
    }

    void pause(void) noexcept {
        _paused = true;
        _pause = std::chrono::system_clock::now();
    }

    void resume(void) noexcept {
        auto cast = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now() - _pause
        );
        _chrono += cast;
        _paused = false;
    }

    bool isPaused(void) const noexcept {
        return _paused;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> _chrono, _pause;
    bool _paused = false;

    template <typename T>
    Uint getAs(void) const noexcept {
        auto dt = _paused ? _pause : std::chrono::system_clock::now();
        return std::chrono::duration_cast<T>(
            dt - _chrono
        ).count();
    }
};