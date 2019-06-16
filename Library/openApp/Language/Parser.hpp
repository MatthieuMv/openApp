/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Parser
*/

#pragma once

#include <openApp/Language/Lexer.hpp>
#include <openApp/App/Item.hpp>

namespace oA { class Parser; }

class oA::Parser
{
public:
    static ItemPtr ParseFile(const String &path);
    static ItemPtr ParseString(const String &toProcess);

private:
    Parser(void) = default;
};