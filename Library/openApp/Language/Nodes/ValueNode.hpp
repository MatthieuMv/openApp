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

    ValueNode(void) = default;

    ValueNode(Var &&var) : value(std::move(var)) {}

    virtual ~ValueNode(void) = default;

    virtual NodeType getType(void) const { return Value; }

    virtual VarRef compute(void) override { return value; }

};