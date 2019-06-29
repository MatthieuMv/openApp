/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operator
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Language/Operator.hpp>

static const oA::UMap<oA::String, oA::OperatorModel> OperatorMap = {
    { "+", { oA::Addition,          2 } },
    { "-", { oA::Substraction,      2 } },
    { "*", { oA::Multiplication,    2 } },
    { "/", { oA::Division,          2 } },
    { "%", { oA::Modulo,            2 } }
};

bool oA::IsOperator(const oA::String &op)
{
    return OperatorMap.find(op) != OperatorMap.end();
}

const oA::OperatorModel &oA::GetOperator(const oA::String &op)
{
    auto it = OperatorMap.find(op);

    if (it == OperatorMap.end())
        throw AccessError("Operator", "Can't find operator @" + op + "@");
    return it->second;
}