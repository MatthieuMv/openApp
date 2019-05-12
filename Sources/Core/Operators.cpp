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
    { "!",  { oA::Not,      oA::RightToLeft, 4  } },
    { "*",  { oA::Mult,     oA::LeftToRight, 5  } },
    { "/",  { oA::Div,      oA::LeftToRight, 5  } },
    { "%",  { oA::Mod,      oA::LeftToRight, 5  } },
    { "+",  { oA::Add,      oA::LeftToRight, 6  } },
    { "-",  { oA::Sub,      oA::LeftToRight, 6  } },
    { ">",  { oA::Sup,      oA::LeftToRight, 8  } },
    { "<",  { oA::Inf,      oA::LeftToRight, 8  } },
    { ">=", { oA::SupEq,    oA::LeftToRight, 8  } },
    { "<=", { oA::InfEq,    oA::LeftToRight, 8  } },
    { "==", { oA::Eq,       oA::LeftToRight, 9  } },
    { "!=", { oA::Diff,     oA::LeftToRight, 9  } },
    { "&&", { oA::And,      oA::LeftToRight, 13 } },
    { "||", { oA::Or,       oA::LeftToRight, 14 } },
    { "?",  { oA::If,       oA::RightToLeft, 15 } },
    { ":",  { oA::Else,     oA::RightToLeft, 15 } },
    { "(",  { oA::LP,       oA::LeftToRight, 16  } },
    { ")",  { oA::RP,       oA::LeftToRight, 16  } }
};

bool oA::OperatorExists(const String &op)
{
    return C_OPERATORS.find(op) != C_OPERATORS.end();
}

const oA::Operator &oA::GetOperator(const String &op)
{
    auto it = C_OPERATORS.find(op);

    if (it == C_OPERATORS.end())
        throw AccessError("Operators", "Coudldn't find operator @" + op + "@");
    return (it->second);
}

void oA::FormatExpression(String &expr)
{
    auto last = expr.begin();

    for (auto it = expr.begin(); last != expr.end() && it != expr.end(); ++it) {
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