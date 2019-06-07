/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operators
*/

#include <openApp/Types/Error.hpp>
#include <openApp/Core/Operator.hpp>

static bool MatchOperator(oA::String &expr, const oA::String &op, oA::String::iterator &it, const oA::String::iterator last);

static const oA::RPN::OperatorMap C_OPERATORS = {
    { ";",  { oA::RPN::Separator,            oA::RPN::NoneFlow,    90 } },
    { "()", { oA::RPN::Call,                 oA::RPN::LeftToRight, 80 } },
    { "(",  { oA::RPN::LeftParenthesis,      oA::RPN::NoneFlow,    90 } },
    { ")",  { oA::RPN::RightParenthesis,     oA::RPN::NoneFlow,    90 } },
    { "?",  { oA::RPN::If,                   oA::RPN::NoneFlow,    90 } },
    { ":",  { oA::RPN::Else,                 oA::RPN::NoneFlow,    90 } },
    { "+=", { oA::RPN::AdditionAssign,       oA::RPN::RightToLeft, 70 } },
    { "-=", { oA::RPN::SubstractionAssign,   oA::RPN::RightToLeft, 70 } },
    { "*=", { oA::RPN::MultiplicationAssign, oA::RPN::RightToLeft, 70 } },
    { "/=", { oA::RPN::DivisionAssign,       oA::RPN::RightToLeft, 70 } },
    { "%=", { oA::RPN::ModuloAssign,         oA::RPN::RightToLeft, 70 } },
    { "==", { oA::RPN::Equal,                oA::RPN::LeftToRight, 40 } },
    { "!=", { oA::RPN::Diff,                 oA::RPN::LeftToRight, 40 } },
    { "&&", { oA::RPN::And,                  oA::RPN::LeftToRight, 50 } },
    { "||", { oA::RPN::Or,                   oA::RPN::LeftToRight, 50 } },
    { "=",  { oA::RPN::Assign,               oA::RPN::RightToLeft, 70 } },
    { "!",  { oA::RPN::Not,                  oA::RPN::RightToLeft, 5  } },
    { "*",  { oA::RPN::Multiplication,       oA::RPN::LeftToRight, 10 } },
    { "/",  { oA::RPN::Division,             oA::RPN::LeftToRight, 10 } },
    { "%",  { oA::RPN::Modulo,               oA::RPN::LeftToRight, 10 } },
    { "+",  { oA::RPN::Addition,             oA::RPN::LeftToRight, 20 } },
    { "-",  { oA::RPN::Substraction,         oA::RPN::LeftToRight, 20 } },
    { ">=", { oA::RPN::SuperiorEqual,        oA::RPN::LeftToRight, 30 } },
    { "<=", { oA::RPN::InferiorEqual,        oA::RPN::LeftToRight, 30 } },
    { ">",  { oA::RPN::Superior,             oA::RPN::LeftToRight, 30 } },
    { "<",  { oA::RPN::Inferior,             oA::RPN::LeftToRight, 30 } }
};

bool oA::RPN::OperatorExists(const String &op)
{
    return C_OPERATORS.findIf([&op](auto &pair) { return pair.first == op; }) != C_OPERATORS.end();
}

const oA::RPN::Operator &oA::RPN::GetOperator(const String &op)
{
    auto it = C_OPERATORS.findIf([&op](auto &pair) { return pair.first == op; });

    if (it == C_OPERATORS.end())
        throw AccessError("Operators", "Coudldn't find operator @" + op + "@");
    return (it->second);
}

void oA::RPN::FormatExpression(String &expr)
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

oA::String oA::RPN::GetOperatorString(oA::RPN::OperatorType op)
{
    for (auto &node : C_OPERATORS) {
        if (node.second.type == op)
            return node.first;
    }
    return String();
}