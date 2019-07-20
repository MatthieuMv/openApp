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
    String name, id;

    ClassNode(String &&className, String &&itemID) : name(std::move(className)), id(std::move(itemID)) {}

    virtual ~ClassNode(void) = default;
    
    virtual NodeType getType(void) const { return Class; }
};