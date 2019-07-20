/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ValueNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>

namespace oA::Lang { struct ValueNode; }

struct oA::Lang::ValueNode : public ASTNode
{
    Var value;

    virtual ~ValueNode(void) = default;
    
    virtual NodeType getType(void) const { return Value; }
    
    virtual Var compute(void) override { return value; }

};