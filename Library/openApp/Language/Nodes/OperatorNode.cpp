/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OperatorNode
*/

#include <openApp/Core/Log.hpp>
#include <openApp/Language/Nodes/OperatorNode.hpp>
#include <openApp/Language/Nodes/ReferenceNode.hpp>

oA::Lang::VarRef oA::Lang::OperatorNode::compute(void)
{
    switch (op) {
    case Not:
        return computeUnary(&Var::operator!);
    case Equal:
        return computeBinary(&Var::operator==);
    case Different:
        return computeBinary(&Var::operator!=);
    case Superior:
        return computeBinary(&Var::operator>);
    case SuperiorEqual:
        return computeBinary(&Var::operator>=);
    case Inferior:
        return computeBinary(&Var::operator<);
    case InferiorEqual:
        return computeBinary(&Var::operator<=);
    case Addition:
        return computeBinary(&Var::operator+);
    case Substraction:
        return computeBinary(&Var::operator-);
    case Multiplication:
        return computeBinary(&Var::operator*);
    case Division:
        return computeBinary(&Var::operator/);
    case Modulo:
        return computeBinary(&Var::operator%);
    case Assign:
        return computeBinaryAssignment();
    case AdditionAssign:
        return computeBinaryAssignment(&Var::operator+=);
    case SubstractionAssign:
        return computeBinaryAssignment(&Var::operator-=);
    case MultiplicationAssign:
        return computeBinaryAssignment(&Var::operator*=);
    case DivisionAssign:
        return computeBinaryAssignment(&Var::operator/=);
    case ModuloAssign:
        return computeBinaryAssignment(&Var::operator%=);
    case PrefixIncrement:
        return computeUnaryAssignment(static_cast<Var&(Var::*)(void)>(&Var::operator++));
    case PrefixDecrement:
        return computeUnaryAssignment(static_cast<Var&(Var::*)(void)>(&Var::operator--));
    case SufixIncrement:
        return computeUnarySufixAssignment(static_cast<Var(Var::*)(Int)>(&Var::operator++));
    case SufixDecrement:
        return computeUnarySufixAssignment(static_cast<Var(Var::*)(Int)>(&Var::operator--));
    case At:
        return children[0]->compute()->operator[](*children[1]->compute());
    case TernaryIf:
        return *children[0]->compute() ? children[1]->compute() : children[2]->compute();
    case Call:
    {
        auto &property = *dynamic_cast<ReferenceNode &>(*children[0]).ptr;
        property.call();
        return property;
    }
    default:
        throw LogicError("OperatorNode", "Can't compute uncomputable operator");
    }
}