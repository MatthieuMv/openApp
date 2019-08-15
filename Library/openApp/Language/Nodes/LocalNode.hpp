/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** LocalNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>

namespace oA::Lang { struct LocalNode; }

struct oA::Lang::LocalNode : public ASTNode
{
    Var &local;

    LocalNode(Var &ref) : local(ref) {}

    virtual ~LocalNode(void) = default;

    virtual NodeType getType(void) const { return Local; }

    virtual bool isConst(void) const { return false; }

    Var compute(void) { return local; }
};