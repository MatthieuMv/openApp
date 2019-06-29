/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Statement
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Language/Statement.hpp>

static const oA::UMap<oA::String, oA::StatementModel> StatementMap = {
    { "var",    { oA::Declaration   } },        
    { "if",     { oA::Condition     } },    
    { "while",  { oA::While         } },
    { "for",    { oA::For           } },
    { "switch", { oA::Switch        } }
};

bool oA::IsStatement(const oA::String &statement)
{
    return StatementMap.find(statement) != StatementMap.end();
}

const oA::StatementModel &oA::GetStatement(const oA::String &statement)
{
    auto it = StatementMap.find(statement);

    if (it == StatementMap.end())
        throw AccessError("Statement", "Can't find statement @" + statement + "@");
    return it->second;
}