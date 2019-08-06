/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operator
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Language/Operator.hpp>

static const oA::UMap<oA::String, oA::Lang::OperatorModel> OperatorMap = {
    { "!",      { oA::Lang::Not,                    1,  16,     oA::Lang::RightToLeft           }    },
    { "+",      { oA::Lang::Addition,               2,  13,     oA::Lang::LeftToRight           }    },
    { "-",      { oA::Lang::Substraction,           2,  13,     oA::Lang::LeftToRight           }    },
    { "*",      { oA::Lang::Multiplication,         2,  14,     oA::Lang::LeftToRight           }    },
    { "/",      { oA::Lang::Division,               2,  14,     oA::Lang::LeftToRight           }    },
    { "%",      { oA::Lang::Modulo,                 2,  5,      oA::Lang::LeftToRight           }    },
    { "=",      { oA::Lang::Assign,                 2,  3,      oA::Lang::RightToLeft           }    },
    { "+=",     { oA::Lang::AdditionAssign,         2,  3,      oA::Lang::RightToLeft           }    },
    { "-=",     { oA::Lang::SubstractionAssign,     2,  3,      oA::Lang::RightToLeft           }    },
    { "*=",     { oA::Lang::MultiplicationAssign,   2,  3,      oA::Lang::RightToLeft           }    },
    { "/=",     { oA::Lang::DivisionAssign,         2,  3,      oA::Lang::RightToLeft           }    },
    { "%=",     { oA::Lang::ModuloAssign,           2,  3,      oA::Lang::RightToLeft           }    },
    { "++",     { oA::Lang::PrefixIncrement,        1,  16,     oA::Lang::RightToLeft           }    },
    { "--",     { oA::Lang::PrefixDecrement,        1,  16,     oA::Lang::RightToLeft           }    },
    { "++",     { oA::Lang::SufixIncrement,         1,  17,     oA::Lang::LeftToRight           }    },
    { "--",     { oA::Lang::SufixDecrement,         1,  17,     oA::Lang::LeftToRight           }    },
    { "==",     { oA::Lang::Equal,                  2,  10,     oA::Lang::LeftToRight           }    },
    { "!=",     { oA::Lang::Different,              2,  10,     oA::Lang::LeftToRight           }    },
    { ">",      { oA::Lang::Superior,               2,  11,     oA::Lang::LeftToRight           }    },
    { "<",      { oA::Lang::Inferior,               2,  11,     oA::Lang::LeftToRight           }    },
    { ">=",     { oA::Lang::SuperiorEqual,          2,  11,     oA::Lang::LeftToRight           }    },
    { "<=",     { oA::Lang::InferiorEqual,          2,  11,     oA::Lang::LeftToRight           }    },
    { ";",      { oA::Lang::End,                    0,  22,     oA::Lang::NoneAssociativity     }    },
    { ",",      { oA::Lang::Comma,                  0,  21,     oA::Lang::NoneAssociativity     }    },
    { "?",      { oA::Lang::TernaryIf,              3,  1,      oA::Lang::RightToLeft           }    },
    { ":",      { oA::Lang::TernaryElse,            0,  0,      oA::Lang::RightToLeft           }    },
    { "(",      { oA::Lang::LeftParenthese,         0,  0,      oA::Lang::NoneAssociativity     }    },
    { ")",      { oA::Lang::RightParenthese,        0,  0,      oA::Lang::NoneAssociativity     }    },
    { "{",      { oA::Lang::LeftBrace,              0,  0,      oA::Lang::NoneAssociativity     }    },
    { "}",      { oA::Lang::RightBrace,             0,  0,      oA::Lang::NoneAssociativity     }    },
    { "[",      { oA::Lang::LeftBracket,            0,  0,      oA::Lang::LeftToRight           }    },
    { "]",      { oA::Lang::RightBracket,           0,  0,      oA::Lang::NoneAssociativity     }    },
    { "()",     { oA::Lang::Call,                   1,  20,     oA::Lang::LeftToRight           }    },
    { "[]",     { oA::Lang::At,                     2,  19,     oA::Lang::LeftToRight           }    }
};

bool oA::Lang::IsOperator(const oA::String &op)
{
    return OperatorMap.find(op) != OperatorMap.end();
}

const oA::Lang::OperatorModel &oA::Lang::GetOperator(const oA::String &op)
{
    auto it = OperatorMap.find(op);

    if (it == OperatorMap.end())
        throw AccessError("Operator", "Can't find operator @" + op + "@");
    return it->second;
}

const oA::Lang::OperatorModel &oA::Lang::GetOperator(Operator op)
{
    return OperatorMap.findIf([op](const auto &p) {
        return p.second.type == op;
    })->second;
}

const oA::String &oA::Lang::GetOperatorSymbol(Operator op)
{
    return OperatorMap.findIf([op](const auto &p) {
        return p.second.type == op;
    })->first;
}