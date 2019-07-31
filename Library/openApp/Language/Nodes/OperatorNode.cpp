/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OperatorNode
*/

#include <openApp/Language/Nodes/OperatorNode.hpp>
#include <openApp/Language/Nodes/ReferenceNode.hpp>
#include <openApp/Language/Nodes/LocalNode.hpp>
#include <openApp/Containers/Pair.hpp>

oA::Var oA::Lang::OperatorNode::compute(void)
{
    switch (op) {
    case Not:
        return !children[0]->compute();
    case Equal:
        return children[0]->compute() == children[1]->compute();
    case Different:
        return children[0]->compute() != children[1]->compute();
    case Superior:
        return children[0]->compute() > children[1]->compute();
    case SuperiorEqual:
        return children[0]->compute() >= children[1]->compute();
    case Inferior:
        return children[0]->compute() < children[1]->compute();
    case InferiorEqual:
        return children[0]->compute() <= children[1]->compute();
    case Addition:
        return children[0]->compute() + children[1]->compute();
    case Substraction:
        return children[0]->compute() - children[1]->compute();
    case Multiplication:
        return children[0]->compute() * children[1]->compute();
    case Division:
        return children[0]->compute() / children[1]->compute();
    case Modulo:
        return children[0]->compute() % children[1]->compute();
    case Assign:
        return assign(*children[0], children[1]->compute(), op);
    case AdditionAssign:
        return assign(*children[0], children[1]->compute(), op);
    case SubstractionAssign:
        return assign(*children[0], children[1]->compute(), op);
    case MultiplicationAssign:
        return assign(*children[0], children[1]->compute(), op);
    case DivisionAssign:
        return assign(*children[0], children[1]->compute(), op);
    case ModuloAssign:
        return assign(*children[0], children[1]->compute(), op);
    case PrefixIncrement:
        return assign(*children[0], 1, AdditionAssign);
    case PrefixDecrement:
        return assign(*children[0], 1, SubstractionAssign);
    case SufixIncrement:
    {
        auto var = children[0]->compute();
        assign(*children[0], 1, AdditionAssign);
        return var;
    }
    case SufixDecrement:
    {
        auto var = children[0]->compute();
        assign(*children[0], 1, SubstractionAssign);
        return var;
    }
    case Call:
    {
        auto &expr = *dynamic_cast<ReferenceNode &>(*children[0]).ptr;
        expr.call();
        return *expr;
    }
    case At:
        return at();
    case TernaryIf:
        return children[0]->compute() ? children[1]->compute() : children[2]->compute();
    default:
        throw LogicError("OperatorNode", "Can't compute uncomputable operator");
    }
}

oA::Var &oA::Lang::OperatorNode::at(void)
{
    auto index = children[1]->compute();

    switch (children[0]->getType()) {
    case Reference:
        return dynamic_cast<ReferenceNode &>(*children[0]).ptr->getRaw()[index];
    case Local:
        return dynamic_cast<LocalNode &>(*children[0]).local[index];
    default:
        throw LogicError("OperatorNode", "Invalid node for operator @at@");
    }
}

oA::Var oA::Lang::OperatorNode::assign(ASTNode &node, Var &&value, Lang::Operator type)
{
    switch (node.getType()) {
    case Reference:
    {
        auto &var = *dynamic_cast<ReferenceNode &>(node).ptr;
        assignValue(var, std::move(value), type);
        return *var;
    }
    case Local:
    {
        auto &var = dynamic_cast<LocalNode &>(node).local;
        assignValue(var, std::move(value), type);
        return var;
    }
    case Operator:
        return assignAt(dynamic_cast<OperatorNode &>(node), std::move(value), type);
    default:
        throw LogicError("OperatorNode", "Invalid assignment");
    }
}

oA::Var &oA::Lang::OperatorNode::assignAt(OperatorNode &node, Var &&value, Lang::Operator type)
{
    auto &var = node.at();
    auto tmp = var;

    assignValue(var, std::move(value), type);
    if (tmp != var && node.children[0]->getType() == Reference)
        dynamic_cast<ReferenceNode &>(*node.children[0]).ptr->emit();
    return var;
}