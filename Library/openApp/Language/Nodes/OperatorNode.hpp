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

    virtual VarRef compute(void);

private:
    template<typename VarFct>
    VarRef computeUnary(VarFct fct) {
        auto v1 = children[0]->compute();
        if (v1.hasOwnership()) {
            *v1 = ((*v1).*fct)();
            return v1;
        }
        return Var(((*v1).*fct)());
    }

    template<typename VarFct>
    VarRef computeBinary(VarFct fct) {
        auto v1 = children[0]->compute(), v2 = children[1]->compute();
        if (v1.hasOwnership()) {
            *v1 = ((*v1).*fct)(*v2);
            return v1;
        } else if (v2.hasOwnership()) {
            *v2 = ((*v1).*fct)(*v2);
            return v2;
        }
        return Var(((*v1).*fct)(*v2));
    }

    VarRef computeBinaryAssignment(void) {
        auto v1 = children[0]->compute(), v2 = children[1]->compute();
        *v1 = v2.hasOwnership() ? std::move(*v2) : *v2;
        return v1;
    }

    template<typename VarFct>
    VarRef computeUnaryAssignment(VarFct fct) {
        auto v1 = children[0]->compute();
        ((*v1).*fct)();
        return v1;
    }

    template<typename VarFct>
    VarRef computeUnarySufixAssignment(VarFct fct) {
        auto v1 = children[0]->compute(), v2 = VarRef(Var(*v1));
        ((*v1).*fct)(0);
        return v2;
    }

    template<typename VarFct>
    VarRef computeBinaryAssignment(VarFct fct) {
        auto v1 = children[0]->compute(), v2 = children[1]->compute();
        ((*v1).*fct)(*v2);
        return v1;
    }
};