/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ReferenceNode
*/

#pragma once

#include <openApp/Core/Expression.hpp>
#include <openApp/Language/ASTNode.hpp>

namespace oA::Lang { struct ReferenceNode; }

struct oA::Lang::ReferenceNode : public ASTNode
{
    ExpressionPtr ptr;

    ReferenceNode(ExpressionPtr &&expression) : ptr(std::move(expression)) {}

    virtual ~ReferenceNode(void) = default;
    
    virtual NodeType getType(void) const { return Reference; }

    virtual Var compute(void) override { return ptr->get(); }
};