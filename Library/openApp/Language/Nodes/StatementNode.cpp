/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** StatementNode
*/

#include <openApp/Language/Nodes/StatementNode.hpp>
#include <openApp/Language/Nodes/LocalNode.hpp>
#include <openApp/Language/Nodes/ValueNode.hpp>

oA::Lang::VarRef oA::Lang::StatementNode::compute(void)
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

oA::Lang::VarRef oA::Lang::StatementNode::computeIf(void)
{
    if (*children[0]->compute())
        return children[1]->compute();
    else if (children.size() == 3)
        return children[2]->compute();
    return VarRef();
}

oA::Lang::VarRef oA::Lang::StatementNode::computeSwitch(void)
{
    try {
        auto it = children.begin();
        VarRef comp = (*it)->compute();

        ++it;
        if (it == children.end())
            return VarRef();
        auto &caseNode = **it;
        for (auto tmp = caseNode.children.begin(); tmp != caseNode.children.end(); tmp += 2) {
            if (*comp == *(*tmp)->compute())
                return (*++tmp)->compute();
        }
        ++it;
        if (it == children.end())
            return VarRef();
        return (*it)->compute();
    } catch (const BreakSignal &) {
        return VarRef();
    }
}

oA::Lang::VarRef oA::Lang::StatementNode::computeWhile(void)
{
    try {
        auto &comp = *children[0];
        auto &group = *children[1];

        while (*comp.compute())
            group.compute();
        return VarRef();
    } catch (const BreakSignal &) {
        return VarRef();
    }
}

oA::Lang::VarRef oA::Lang::StatementNode::computeFor(void)
{
    try {
        auto &comp = *children[1];
        auto &sufix = *children[2];
        auto &group = *children[3];

        for (children[0]->compute(); *comp.compute(); sufix.compute())
            group.compute();
        return VarRef();
    } catch (const BreakSignal &) {
        return VarRef();
    }
}