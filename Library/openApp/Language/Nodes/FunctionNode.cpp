/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** FunctionNode
*/

#include <openApp/Core/Log.hpp>
#include <openApp/Language/Nodes/FunctionNode.hpp>

oA::Lang::VarRef oA::Lang::FunctionNode::compute(void)
{
    switch (symbol) {
    case ToNumber:
        return Var(children[0]->compute()->toFloat());
    case ToLiteral:
        return Var(children[0]->compute()->toString());
    case Length:
        return children[0]->compute()->len();
    case Push:
    {
        auto value = children[1]->compute();
        return children[0]->compute()->push(value.hasOwnership() ? std::move(*value) : *value);
    }
    case Pop:
        return children[0]->compute()->pop();
    case Insert:
    {
        auto value = children[2]->compute();
        return children[0]->compute()->insert(*children[1]->compute(), value.hasOwnership() ? std::move(*value) : *value);
    }
    case Remove:
        return children[0]->compute()->remove(*children[1]->compute());
    case Print:
        for (auto &arg : children)
            cout << arg->compute()->toString();
        cout << endl;
        return VarRef();
    default:
        return VarRef();
    }
}