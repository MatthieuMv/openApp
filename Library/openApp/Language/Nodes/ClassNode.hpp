/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ClassNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>

namespace oA::Lang { struct ClassNode; }

struct oA::Lang::ClassNode : public ASTNode
{
    String name;
    UInt line = 0;

    ClassNode(String &&className, UInt contextLine = 0) : name(std::move(className)), line(contextLine) {}

    virtual ~ClassNode(void) = default;

    virtual NodeType getType(void) const { return Class; }
};