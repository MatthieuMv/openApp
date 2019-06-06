/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Thread
*/

#pragma once

// std::mutex
#include <mutex>

namespace oA
{
    /**
     * @brief A simple std::mutex
     */
    using Mutex = std::mutex;

    /**
     * @brief A simple std::unique_lock based on Mutex
     */
    using UniqueLock = std::unique_lock<Mutex>;
}