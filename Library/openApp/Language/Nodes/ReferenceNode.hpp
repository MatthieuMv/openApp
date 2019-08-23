/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ReferenceNode
*/

#pragma once

#include <openApp/Core/Property.hpp>
#include <openApp/Language/ASTNode.hpp>

namespace oA::Lang { struct ReferenceNode; }

struct oA::Lang::ReferenceNode : public ASTNode
{
    PropertyPtr ptr;

    ReferenceNode(PropertyPtr &&property) : ptr(std::move(property)) {}

    virtual ~ReferenceNode(void) = default;

    virtual NodeType getType(void) const { return Reference; }

    virtual bool isConst(void) const { return false; }

    virtual VarRef compute(void) override { return *ptr; }
};