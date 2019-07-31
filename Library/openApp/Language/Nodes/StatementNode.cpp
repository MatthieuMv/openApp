/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** StatementNode
*/

#include <openApp/Language/Nodes/StatementNode.hpp>

oA::Var oA::Lang::StatementNode::compute(void)
{
    switch (statement) {
    case If:
        return computeIf();
    case Switch:
        return computeSwitch();
    case While:
        return computeWhile();
    case For:
        return computeFor();
    case Break:
        throw BreakSignal();
    case Return:
        throw ReturnSignal(children[0]->compute());
    default:
        throw LogicError("StatementNode", "Can't compute uncomputable statement");
    }
}

oA::Var oA::Lang::StatementNode::computeIf(void)
{
    if (children[0]->compute())
        return children[1]->compute();
    else if (children.size() == 3)
        return children[2]->compute();
    return Var();
}

oA::Var oA::Lang::StatementNode::computeSwitch(void)
{
    auto it = children.begin();
    auto next = it + 1;
    auto end = children.end();
    Var comp = (*it)->compute();

    for (++it; it != children.end(); ++it) {
        if (next == end)
            return (*it)->compute();
        else if ((*it)->compute() == comp)
            return (*next)->compute();
        ++next;
    }
    return Var();
}

oA::Var oA::Lang::StatementNode::computeWhile(void)
{
    auto &comp = children[0];
    auto &group = children[1];
    Var var;

    while (comp->compute()) {
        var = group->compute();
    }
    return var;
}

oA::Var oA::Lang::StatementNode::computeFor(void)
{
    auto &comp = children[1];
    auto &sufix = children[2];
    auto &group = children[3];
    Var var;

    for (children[0]->compute(); comp->compute(); sufix->compute()) {
        var = group->compute();
    }
    return var;
}