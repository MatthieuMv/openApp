/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** StatementNode
*/

#include <openApp/Language/Nodes/StatementNode.hpp>
#include <openApp/Language/Nodes/LocalNode.hpp>
#include <openApp/Language/Nodes/ValueNode.hpp>

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
    try {
        auto it = children.begin();
        Var comp = (*it)->compute();
        auto end = children.end();

        for (++it; it != children.end(); it += 2) {
            if (it + 1 == end)
                return (*it)->compute();
            else if ((*it)->compute() == comp)
                return (*++it)->compute();
        }
        return Var();
    } catch (const BreakSignal &) {
        return Var();
    }
}

oA::Var oA::Lang::StatementNode::computeWhile(void)
{
    try {
        auto &comp = *children[0];
        auto &group = *children[1];

        while (comp.compute())
            group.compute();
        return Var();
    } catch (const BreakSignal &) {
        return Var();
    }
}

oA::Var oA::Lang::StatementNode::computeFor(void)
{
    try {
        auto &comp = *children[1];
        auto &sufix = *children[2];
        auto &group = *children[3];

        for (children[0]->compute(); comp.compute(); sufix.compute())
            group.compute();
        return Var();
    } catch (const BreakSignal &) {
        return Var();
    }
}