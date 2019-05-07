/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Parser
*/

#pragma once

// String
#include "Core/String.hpp"

namespace oA { class Parser; }

class oA::Parser
{
public:
    struct Token
    {
        String context;
        String data;
    };

    struct ContextMatch
    {
        String matchContext;
        String matchData;
        String beginData;
        String endData;
    };

public:
    Parser(void) = default;

    Token &token(void) noexcept { return (_token); }
    const Token &token(void) const noexcept { return (_token); }

    bool retreiveContext(const ContextMatch &match);

protected:
    Token _token;
};