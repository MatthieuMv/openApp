/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Memory
*/

#pragma once

// std::unique/shared/weak_ptr
#include <memory>

namespace oA
{
    template<typename T, typename D = std::default_delete<T>>
    using Unique = std::unique_ptr<T, D>;

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T>
    using Weak = std::weak_ptr<T>;

    template<typename T, typename ...Args>
    Unique<T> MakeUnique(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

    template<typename T, typename ...Args>
    Shared<T> MakeShared(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }
}