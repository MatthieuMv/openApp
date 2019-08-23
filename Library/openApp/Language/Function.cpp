/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Function
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Language/Function.hpp>

static const oA::UMap<oA::String, oA::Lang::FunctionModel> FunctionMap = {
    { "toNumber",       {   oA::Lang::ToNumber,     1   }   },
    { "toLiteral",      {   oA::Lang::ToLiteral,    1   }   },
    { "len",            {   oA::Lang::Length,       1   }   },
    { "push",           {   oA::Lang::Push,         2   }   },
    { "pop",            {   oA::Lang::Pop,          1   }   },
    { "insert",         {   oA::Lang::Insert,       3   }   },
    { "remove",         {   oA::Lang::Remove,       2   }   },
    { "print",          {   oA::Lang::Print,        -1  }   }
};

bool oA::Lang::IsFunction(const oA::String &statement)
{
    return FunctionMap.find(statement) != FunctionMap.end();
}

const oA::Lang::FunctionModel &oA::Lang::GetFunction(const oA::String &statement)
{
    auto it = FunctionMap.find(statement);

    if (it == FunctionMap.end())
        throw AccessError("Function", "Can't find Function @" + statement + "@");
    return it->second;
}

const oA::Lang::FunctionModel &oA::Lang::GetFunction(Function statement)
{
    return FunctionMap.findIf([statement](const auto &p) {
        return p.second.type == statement;
    })->second;
}

const oA::String &oA::Lang::GetFunctionSymbol(Function statement)
{
    return FunctionMap.findIf([statement](const auto &p) {
        return p.second.type == statement;
    })->first;
}