/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OperatorNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>
#include <openApp/Language/Operator.hpp>

namespace oA::Lang { struct OperatorNode; }

struct oA::Lang::OperatorNode : public ASTNode
{
    Lang::Operator op;

    OperatorNode(Lang::Operator Op) : op(Op) {}

    virtual ~OperatorNode(void) = default;
    
    virtual NodeType getType(void) const { return NodeType::Operator; }
};