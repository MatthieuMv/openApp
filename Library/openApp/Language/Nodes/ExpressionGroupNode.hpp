/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionGroupNode
*/

#pragma once

#include <openApp/Language/Nodes/GroupNode.hpp>
#include <openApp/Containers/UMap.hpp>

namespace oA::Lang { struct ExpressionGroupNode; }

struct oA::Lang::ExpressionGroupNode : public GroupNode
{
    UMap<String, Var> locals;

    virtual ~ExpressionGroupNode(void) = default;

    virtual NodeType getType(void) const { return ExpressionGroup; }

    virtual VarRef compute(void) override {
        try {
            return GroupNode::compute();
        } catch (ReturnSignal &ret) {
            return std::move(ret.value);
        } catch (const BreakSignal &) {
            throw LogicError("Break statement used out of loop");
        }
    }
};