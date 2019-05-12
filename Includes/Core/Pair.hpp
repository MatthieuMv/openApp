/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Tuple
*/

#pragma once

namespace oA
{
    template<typename A, typename B>
    using Pair = std::pair<A, B>;

    template<typename A, typename B>
    auto MakePair(A &&a, B &&b) { return std::make_pair(a, b); }
}