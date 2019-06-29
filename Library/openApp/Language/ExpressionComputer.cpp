/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionComputer
*/

#include <openApp/Types/Function.hpp>
#include <openApp/Language/ExpressionComputer.hpp>

oA::Var oA::ExpressionComputer::Compute(Tree<ExpressionNode> &tree)
{
    return ExpressionComputer().compute(tree);
}

oA::Var oA::ExpressionComputer::compute(Tree<ExpressionNode> &node)
{
    switch (node.value.index()) {
    case ExpressionNode::ValueNode:
        return node.value.getAs<Var>();
    case ExpressionNode::LocalNode:
        return _locals[node.value.getAs<String>()];
    case ExpressionNode::MemberNode:
        return node.value.getAs<ExpressionPtr>()->get();
    case ExpressionNode::OperatorNode:
        return computeOperator(node);
    case ExpressionNode::StatementNode:
        return computeStatement(node);
    default:
        return Var();
    }
}

oA::Var oA::ExpressionComputer::computeStatement(Tree<ExpressionNode> &node)
{
    switch (node.value.getAs<Statement>()) {
    case Block:
        return computeBlock(node);
    case Declaration:
        return computeDeclaration(node);
    case Condition:
        return computeCondition(node);
    case While:
        return computeWhile(node);
    case For:
        return computeFor(node);
    case Switch:
        return computeSwitch(node);
    default:
        return Var();
    }
}

oA::Var oA::ExpressionComputer::computeBlock(Tree<ExpressionNode> &node)
{
    oA::Var res;

    for (auto &child : node.children) {
        res = compute(child);
    }
    return res;
}

oA::Var oA::ExpressionComputer::computeDeclaration(Tree<ExpressionNode> &node)
{
    return _locals[node.children[0].value.getAs<Var>().getAs<String>()] = compute(node.children[1]);
}

oA::Var oA::ExpressionComputer::computeCondition(Tree<ExpressionNode> &node)
{
    auto it = node.children.begin(), end = node.children.end();

    for (auto conditions = node.children.size() / 2; conditions-- && it != end; ++it) {
        if (compute(*it))
            return compute(*++it);
    }
    if (it != end)
        return compute(*it);
    return Var();
}

oA::Var oA::ExpressionComputer::computeWhile(Tree<ExpressionNode> &node)
{
    auto &conditionNode(node.children[0]);
    auto &blockNode(node.children[1]);

    while (compute(conditionNode))
        compute(blockNode);
    return Var();
}

oA::Var oA::ExpressionComputer::computeFor(Tree<ExpressionNode> &node)
{
    auto &declarationNode(node.children[0]);
    auto &conditionNode(node.children[1]);
    auto &iterationNode(node.children[2]);
    auto &blockNode(node.children[3]);

    for (compute(declarationNode); compute(conditionNode); compute(iterationNode))
        compute(blockNode);
    return Var();
}

oA::Var oA::ExpressionComputer::computeSwitch(Tree<ExpressionNode> &node)
{
    auto it = node.children.begin(), end = node.children.end();
    auto var(compute(*(it++)));

    for (auto conditions = (node.children.size() - 1) / 2; conditions-- && it != end; ++it) {
        if (var == compute(*it))
            return compute(*++it);
    }
    if (it != end)
        return compute(*it);
    return Var();
}

oA::Var oA::ExpressionComputer::computeOperator(Tree<ExpressionNode> &node)
{
    auto &first(node.children[0]);

    switch (node.value.getAs<Operator>()) {
    case Not:
        return !compute(first);
    case Equal:
        return compute(first) == compute(node.children[1]);
    case Different:
        return compute(first) != compute(node.children[1]);
    case Superior:
        return compute(first) > compute(node.children[1]);
    case SuperiorEqual:
        return compute(first) >= compute(node.children[1]);
    case Inferior:
        return compute(first) < compute(node.children[1]);
    case InferiorEqual:
        return compute(first) <= compute(node.children[1]);
    case Addition:
        return compute(first) + compute(node.children[1]);
    case Substraction:
        return compute(first) - compute(node.children[1]);
    case Division:
        return compute(first) / compute(node.children[1]);
    case Multiplication:
        return compute(first) * compute(node.children[1]);
    case Modulo:
        return compute(first) % compute(node.children[1]);
    case Assign:
        return assignNode(first, compute(node.children[1]));
    case AdditionAssign:
        return assignNode(first, compute(first) + compute(node.children[1]));
    case SubstractionAssign:
        return assignNode(first, compute(first) - compute(node.children[1]));
    case DivisionAssign:
        return assignNode(first, compute(first) / compute(node.children[1]));
    case MultiplicationAssign:
        return assignNode(first, compute(first) * compute(node.children[1]));
    case ModuloAssign:
        return assignNode(first, compute(first) % compute(node.children[1]));
    case PrefixIncrement:
        return assignNode(first, compute(first) + Var(1));
    case PrefixDecrement:
        return assignNode(first, compute(first) - Var(1));
    default:
        return Var();
    }
}

oA::Var oA::ExpressionComputer::assignNode(Tree<ExpressionNode> &node, Var &&res)
{
    switch (node.value.index()) {
    case ExpressionNode::LocalNode:
        return _locals[node.value.getAs<String>()] = res;
    case ExpressionNode::MemberNode:
        auto &expr(node.value.getAs<ExpressionPtr>());
        expr->set(res);
        return expr->get();
    default:
        return Var();
    }
}