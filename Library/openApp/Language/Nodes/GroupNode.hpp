/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** GroupNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>

namespace oA::Lang { struct GroupNode; }

struct oA::Lang::GroupNode : public ASTNode
{
    virtual ~GroupNode(void) = default;

    virtual NodeType getType(void) const { return Group; }

    virtual Var compute(void) override {
        Var res;
        for (const auto &child : children)
            res = child->compute();
        return res;
    }
};