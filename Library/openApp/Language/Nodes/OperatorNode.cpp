/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OperatorNode
*/

#include <openApp/Containers/Pair.hpp>
#include <openApp/Language/Nodes/OperatorNode.hpp>
#include <openApp/Language/Nodes/ReferenceNode.hpp>
#include <openApp/Language/Nodes/LocalNode.hpp>

#include <openApp/Core/Log.hpp>

oA::Lang::VarRef oA::Lang::OperatorNode::compute(void)
{
    switch (op) {
    case Not:
        return !*children[0]->compute();
    case Equal:
        return *children[0]->compute() == *children[1]->compute();
    case Different:
        return *children[0]->compute() != *children[1]->compute();
    case Superior:
        return *children[0]->compute() > *children[1]->compute();
    case SuperiorEqual:
        return *children[0]->compute() >= *children[1]->compute();
    case Inferior:
        return *children[0]->compute() < *children[1]->compute();
    case InferiorEqual:
        return *children[0]->compute() <= *children[1]->compute();
    case Addition:
        return *children[0]->compute() + *children[1]->compute();
    case Substraction:
        return *children[0]->compute() - *children[1]->compute();
    case Multiplication:
        return *children[0]->compute() * *children[1]->compute();
    case Division:
        return *children[0]->compute() / *children[1]->compute();
    case Modulo:
        return *children[0]->compute() % *children[1]->compute();
    case Assign:
        return *children[0]->compute() = *children[1]->compute();
    case AdditionAssign:
        return *children[0]->compute() += *children[1]->compute();
    case SubstractionAssign:
        return *children[0]->compute() -= *children[1]->compute();
    case MultiplicationAssign:
        return *children[0]->compute() *= *children[1]->compute();
    case DivisionAssign:
        return *children[0]->compute() /= *children[1]->compute();
    case ModuloAssign:
        return *children[0]->compute() %= *children[1]->compute();
    case PrefixIncrement:
        return ++(*children[0]->compute());
    case PrefixDecrement:
        return --(*children[0]->compute());
    case SufixIncrement:
        return (*children[0]->compute())++;
    case SufixDecrement:
        return (*children[0]->compute())--;
    case Call:
    {
        auto &property = *dynamic_cast<ReferenceNode &>(*children[0]).ptr;
        property.call();
        return property;
    }
    case At:
        return (*children[0]->compute())[*children[1]->compute()];
    case TernaryIf:
        return *children[0]->compute() ? *children[1]->compute() : *children[2]->compute();
    default:
        throw LogicError("OperatorNode", "Can't compute uncomputable operator");
    }
}