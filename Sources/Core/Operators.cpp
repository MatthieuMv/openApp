/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operators
*/

// Operator
#include "Core/Operators.hpp"
// AccessError
#include "Core/Error.hpp"

static bool MatchOperator(oA::String &expr, const oA::String &op, oA::String::iterator &it, const oA::String::iterator last);

static const oA::OperatorMap C_OPERATORS = {
    { ";",  { oA::Separator,            oA::NoneFlow,    90 } },
    { "()", { oA::Call,                 oA::LeftToRight, 80 } },
    { "(",  { oA::LeftParenthesis,      oA::NoneFlow,    90 } },
    { ")",  { oA::RightParenthesis,     oA::NoneFlow,    90 } },
    { "?",  { oA::If,                   oA::NoneFlow,    90 } },
    { ":",  { oA::Else,                 oA::NoneFlow,    90 } },
    { "+=", { oA::AdditionAssign,       oA::RightToLeft, 70 } },
    { "-=", { oA::SubstractionAssign,   oA::RightToLeft, 70 } },
    { "*=", { oA::MultiplicationAssign, oA::RightToLeft, 70 } },
    { "/=", { oA::DivisionAssign,       oA::RightToLeft, 70 } },
    { "%=", { oA::ModuloAssign,         oA::RightToLeft, 70 } },
    { "==", { oA::Equal,                oA::LeftToRight, 40 } },
    { "!=", { oA::Diff,                 oA::LeftToRight, 40 } },
    { "&&", { oA::And,                  oA::LeftToRight, 50 } },
    { "||", { oA::Or,                   oA::LeftToRight, 50 } },
    { "=",  { oA::Assign,               oA::RightToLeft, 70 } },
    { "!",  { oA::Not,                  oA::RightToLeft, 5  } },
    { "*",  { oA::Multiplication,       oA::LeftToRight, 10 } },
    { "/",  { oA::Division,             oA::LeftToRight, 10 } },
    { "%",  { oA::Modulo,               oA::LeftToRight, 10 } },
    { "+",  { oA::Addition,             oA::LeftToRight, 20 } },
    { "-",  { oA::Substraction,         oA::LeftToRight, 20 } },
    { ">=", { oA::SuperiorEqual,        oA::LeftToRight, 30 } },
    { "<=", { oA::InferiorEqual,        oA::LeftToRight, 30 } },
    { ">",  { oA::Superior,             oA::LeftToRight, 30 } },
    { "<",  { oA::Inferior,             oA::LeftToRight, 30 } }
};

bool oA::OperatorExists(const String &op)
{
    return C_OPERATORS.findIf([&op](auto &pair) { return pair.first == op; }) != C_OPERATORS.end();
}

const oA::Operator &oA::GetOperator(const String &op)
{
    auto it = C_OPERATORS.findIf([&op](auto &pair) { return pair.first == op; });

    if (it == C_OPERATORS.end())
        throw AccessError("Operators", "Coudldn't find operator @" + op + "@");
    return (it->second);
}

void oA::FormatExpression(String &expr)
{
    auto last = expr.begin();
    bool quote = false;

    for (auto it = expr.begin(); last != expr.end() && it != expr.end(); ++it) {
        if (*it == '"')
            quote = !quote;
        if (quote)
            continue;
        for (const auto &op : C_OPERATORS) {
            if (MatchOperator(expr, op.first, it, last))
                break;
        }
        last = it;
    }
}

static bool MatchOperator(oA::String &expr, const oA::String &op, oA::String::iterator &it, const oA::String::iterator last)
{
    auto i = it;
    for (auto c : op) {
        if (*i != c)
            return false;
        ++i;
    }
    if (!std::isspace(*last)) {
        it = expr.insert(it, ' ');
        ++it;
    }
    std::advance(it, op.length());
    if (it != expr.end() && !std::isspace(*it))
        it = expr.insert(it, ' ');
    return true;
}

oA::String oA::GetOperatorString(oA::OperatorType op)
{
    for (auto &node : C_OPERATORS) {
        if (node.second.type == op)
            return node.first;
    }
    return String();
}