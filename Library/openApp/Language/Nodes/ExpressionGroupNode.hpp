/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionGroupNode
*/

#pragma once

#include <openApp/Language/Nodes/GroupNode.hpp>

namespace oA::Lang { struct ExpressionGroupNode; }
 
struct oA::Lang::ExpressionGroupNode : public GroupNode
{
    virtual ~ExpressionGroupNode(void) = default;
    
    virtual NodeType getType(void) const { return ExpressionGroup; }

    UMap<String, Var> locals;
};