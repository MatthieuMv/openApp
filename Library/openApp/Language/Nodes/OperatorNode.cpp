/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OperatorNode
*/

#include <openApp/Language/Nodes/OperatorNode.hpp>
#include <openApp/Language/Nodes/ReferenceNode.hpp>

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
    {
        auto value = children[1]->compute();
        return *children[0]->compute() = value.hasOwnership() ? std::move(*value) : *value;
    }
    case AdditionAssign:
    {
        auto value = children[1]->compute();
        return *children[0]->compute() += value.hasOwnership() ? std::move(*value) : *value;
    }
    case SubstractionAssign:
    {
        auto value = children[1]->compute();
        return *children[0]->compute() -= value.hasOwnership() ? std::move(*value) : *value;
    }
    case MultiplicationAssign:
    {
        auto value = children[1]->compute();
        return *children[0]->compute() *= value.hasOwnership() ? std::move(*value) : *value;
    }
    case DivisionAssign:
    {
        auto value = children[1]->compute();
        return *children[0]->compute() /= value.hasOwnership() ? std::move(*value) : *value;
    }
    case ModuloAssign:
    {
        auto value = children[1]->compute();
        return *children[0]->compute() %= value.hasOwnership() ? std::move(*value) : *value;
    }
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
        return *children[0]->compute() ? children[1]->compute() : children[2]->compute();
    default:
        throw LogicError("OperatorNode", "Can't compute uncomputable operator");
    }
}