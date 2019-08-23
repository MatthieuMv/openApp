/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** FunctionNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>
#include <openApp/Language/Function.hpp>

namespace oA::Lang { struct FunctionNode; }

struct oA::Lang::FunctionNode : public ASTNode
{
    Lang::Function symbol;

    FunctionNode(Lang::Function functionSymbol) : symbol(functionSymbol) {}

    virtual ~FunctionNode(void) = default;

    virtual NodeType getType(void) const { return ASTNode::Function; }

    virtual bool isConst(void) const { return false; }

    virtual VarRef compute(void) override;
};