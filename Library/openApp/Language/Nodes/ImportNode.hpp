/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ImportNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>

namespace oA::Lang { struct ImportNode; }

struct oA::Lang::ImportNode : public ASTNode
{
    String directory;
    Uint line = 0;

    ImportNode(String &&path, Uint contextLine = 0) : directory(std::move(path)), line(contextLine) {}

    virtual ~ImportNode(void) = default;

    virtual NodeType getType(void) const { return Import; }
};
