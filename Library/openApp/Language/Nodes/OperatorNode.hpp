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

    virtual Var compute(void);

    Var &at(void);

    Var assign(ASTNode &node, Var &&value, Lang::Operator type);
    Var &assignAt(OperatorNode &node, Var &&value, Lang::Operator type);

    template<typename T>
    void assignValue(T &var, Var &&value, Lang::Operator type) {
        switch (type) {
        case Assign:
            var = std::move(value); break;
        case AdditionAssign:
            var += std::move(value); break;
        case SubstractionAssign:
            var -= std::move(value); break;
        case MultiplicationAssign:
            var *= std::move(value); break;
        case DivisionAssign:
            var /= std::move(value); break;
        case ModuloAssign:
            var %= std::move(value); break;
        default:
            throw LogicError("OperatorNode", "Invalid assignment operator @" + GetOperatorSymbol(type) + "@");
        }
    }
};