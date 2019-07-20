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

    ImportNode(String &&path) : directory(std::move(path)) {}

    virtual ~ImportNode(void) = default;
    
    virtual NodeType getType(void) const { return Import; }
};
