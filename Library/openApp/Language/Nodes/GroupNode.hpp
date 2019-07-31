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
        try {
            Var res;
            for (const auto &child : children)
                res = child->compute();
            return res;
        } catch (const ReturnSignal &ret) {
            return ret.value;
        } catch (const BreakSignal &) {
            throw LogicError("Break statement used out of loop");
        } catch (...) {
            throw;
        }
    }
};