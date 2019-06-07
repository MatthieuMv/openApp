/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Memory
*/

#pragma once

// std::unique / shared / weak_ptr
#include <memory>

namespace oA
{
    /**
     * @brief A simple std::unique_ptr
     *
     * @tparam T Internal type
     * @tparam D Internal delete
     */
    template<typename T, typename D = std::default_delete<T>>
    using Unique = std::unique_ptr<T, D>;

    /**
     * @brief A simple std::shared_ptr
     *
     * @tparam T Internal type
     */
    template<typename T>
    using Shared = std::shared_ptr<T>;

    /**
     * @brief A simple std::weak_ptr
     *
     * @tparam T Internal type
     */
    template<typename T>
    using Weak = std::weak_ptr<T>;
}