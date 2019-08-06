/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Statement
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Language/Statement.hpp>

static const oA::UMap<oA::String, oA::Lang::StatementModel> StatementMap = {
    { "if",         {   oA::Lang::If                }     },
    { "else",       {   oA::Lang::Else              }     },
    { "switch",     {   oA::Lang::Switch            }     },
    { "case",       {   oA::Lang::Case              }     },
    { "default",    {   oA::Lang::Default           }     },
    { "while",      {   oA::Lang::While             }     },
    { "for",        {   oA::Lang::For               }     },
    { "break",      {   oA::Lang::Break             }     },
    { "return",     {   oA::Lang::Return            }     },
    { "var",        {   oA::Lang::Variable          }     },
    { "static",     {   oA::Lang::StaticVariable    }     }
};

bool oA::Lang::IsStatement(const oA::String &statement)
{
    return StatementMap.find(statement) != StatementMap.end();
}

const oA::Lang::StatementModel &oA::Lang::GetStatement(const oA::String &statement)
{
    auto it = StatementMap.find(statement);

    if (it == StatementMap.end())
        throw AccessError("Statement", "Can't find Statement @" + statement + "@");
    return it->second;
}

const oA::Lang::StatementModel &oA::Lang::GetStatement(Statement statement)
{
    return StatementMap.findIf([statement](const auto &p) {
        return p.second.type == statement;
    })->second;
}

const oA::String &oA::Lang::GetStatementSymbol(Statement statement)
{
    return StatementMap.findIf([statement](const auto &p) {
        return p.second.type == statement;
    })->first;
}