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

/*
    Assign, // =
    AddAssign, SubAssign, MultAssign, DivAssign, ModAssign, // += -= *= /= %=
    PreInc, PreDec, PostInc, PostDec, // ++X --X X++ X--
    Separator // ;
*/

static const oA::OperatorMap C_OPERATORS = {
    { ";",  { oA::LeftParenthesis,      oA::LeftToRight, 0  } },
    { "(",  { oA::LeftParenthesis,      oA::LeftToRight, 0  } },
    { ")",  { oA::RightParenthesis,     oA::LeftToRight, 0  } },
    { "()", { oA::Call,                 oA::LeftToRight, 1  } },
    { "++", { oA::SuffixIncrement,      oA::LeftToRight, 1  } },
    { "--", { oA::SuffixDecrement,      oA::LeftToRight, 1  } },
    { "++", { oA::PrefixIncrement,      oA::RightToLeft, 2  } },
    { "--", { oA::PrefixDecrement,      oA::RightToLeft, 2  } },
    { "!",  { oA::Not,                  oA::RightToLeft, 2  } },
    { "*",  { oA::Multiplication,       oA::LeftToRight, 3  } },
    { "/",  { oA::Division,             oA::LeftToRight, 3  } },
    { "%",  { oA::Modulo,               oA::LeftToRight, 3  } },
    { "+",  { oA::Addition,             oA::LeftToRight, 4  } },
    { "-",  { oA::Substraction,         oA::LeftToRight, 4  } },
    { ">",  { oA::Superior,             oA::LeftToRight, 6  } },
    { "<",  { oA::Inferior,             oA::LeftToRight, 6  } },
    { ">=", { oA::SuperiorEqual,        oA::LeftToRight, 6  } },
    { "<=", { oA::InferiorEqual,        oA::LeftToRight, 6  } },
    { "==", { oA::Equal,                oA::LeftToRight, 7  } },
    { "!=", { oA::Diff,                 oA::LeftToRight, 7  } },
    { "&&", { oA::And,                  oA::LeftToRight, 11 } },
    { "||", { oA::Or,                   oA::LeftToRight, 12 } },
    { "?",  { oA::If,                   oA::RightToLeft, 13 } },
    { ":",  { oA::Else,                 oA::RightToLeft, 13 } },
    { "=",  { oA::Assign,               oA::RightToLeft, 14 } },
    { "+=", { oA::AdditionAssign,       oA::RightToLeft, 14 } },
    { "-=", { oA::SubstractionAssign,   oA::RightToLeft, 14 } },
    { "*=", { oA::MultiplicationAssign, oA::RightToLeft, 14 } },
    { "/=", { oA::DivisionAssign,       oA::RightToLeft, 14 } },
    { "%=", { oA::ModuloAssign,         oA::RightToLeft, 14 } }
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
    bool quote = false;

    for (auto it = expr.begin(); last != expr.end() && it != expr.end(); ++it) {
        if (*it == '"') {
            quote = !quote;
            continue;
        }
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