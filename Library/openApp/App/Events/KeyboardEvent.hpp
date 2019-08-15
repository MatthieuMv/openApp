/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** KeyboardEvent
*/

#pragma once

#include <openApp/Types/V2.hpp>

namespace oA
{
    struct KeyboardEvent;
}

/**
 * @brief Data structure containing a mouse click event
 */
struct oA::KeyboardEvent
{
    enum EventType {
        Pressed,
        Released
    };

    enum KeyType {
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // Alpha
        K0, K1, K2, K3, K4, K5, K6, K7, K8, K9, // Digits
        N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, // Numerical keys
        Up, Left, Right, Down, // Directional keys
        Escape, Return, Space, Backspace
    };

    KeyboardEvent(void) = default;
    KeyboardEvent(EventType eventType, KeyType keyType, Uint eventTime) : type(eventType), key(keyType), timestamp(eventTime) {}

    EventType type = Pressed; // Key state
    KeyType key = A; // Key symbol
    Uint timestamp = 0;
};