/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Chrono
*/

#pragma once

#include <chrono>
#include "Scalar.hpp"

namespace oA { class Chrono; }

class oA::Chrono
{
public:
    Chrono(void) : _chrono(std::chrono::system_clock::now()) {}

    Uint getSeconds(void) const noexcept { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _chrono).count(); }
    Uint getMilliseconds(void) const noexcept { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _chrono).count(); }
    Uint getMicroseconds(void) const noexcept { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - _chrono).count(); }

    void reset(void) noexcept { _chrono = std::chrono::system_clock::now(); }

private:
    std::chrono::time_point<std::chrono::system_clock> _chrono;
};