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

static const oA::OperatorMap C_OPERATORS = {
    { "(",  { oA::LP,       oA::LeftToRight, 2  } },
    { ")",  { oA::RP,       oA::LeftToRight, 2  } },
    { "!",  { oA::Not,      oA::RightToLeft, 5  } },
    { "*",  { oA::Mult,     oA::LeftToRight, 5  } },
    { "/",  { oA::Div,      oA::LeftToRight, 5  } },
    { "%",  { oA::Mod,      oA::LeftToRight, 5  } },
    { "+",  { oA::Add,      oA::LeftToRight, 6  } },
    { "-",  { oA::Sub,      oA::LeftToRight, 6  } },
    { ">",  { oA::Sup,      oA::LeftToRight, 8  } },
    { ">=", { oA::SupEq,    oA::LeftToRight, 8  } },
    { "<",  { oA::Inf,      oA::LeftToRight, 8  } },
    { "<=", { oA::InfEq,    oA::LeftToRight, 8  } },
    { "==", { oA::Eq,       oA::LeftToRight, 9  } },
    { "!=", { oA::Diff,     oA::LeftToRight, 9  } },
    { "&&", { oA::And,      oA::LeftToRight, 13 } },
    { "||", { oA::Or,       oA::LeftToRight, 14 } },
    { "?",  { oA::If,       oA::RightToLeft, 15 } },
    { ":",  { oA::Else,     oA::RightToLeft, 15 } }
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