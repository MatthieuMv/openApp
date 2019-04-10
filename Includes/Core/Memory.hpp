/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Memory
*/

#pragma once

#include <memory>

namespace oA
{
    template<typename T, typename D = std::default_delete<T>>
    using Unique = std::unique_ptr<T, D>;

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T>
    using Weak = std::weak_ptr<T>;
}