/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExprLexer
*/

#include <openApp/Types/SStream.hpp>
#include <openApp/Core/Operator.hpp>
#include <openApp/Language/ExpressionLexer.hpp>

void oA::ExpressionLexer::ProcessString(const String &toProcess, LexTree &target)
{

    ExpressionLexer(ISStream(toProcess), target).process();
}

bool oA::ExpressionLexer::process(const String &end)
{
    static const oA::UMap<String, TokenType> LexMatches = {
    };

    do {
        if (!readToken() || _token == end)
            break;
        auto it = LexMatches.findIf([this](const auto &m) { return std::regex_match(_token, std::regex(m.first)); });
        if (it == LexMatches.end())
            throw LogicError("OALexer", "Couldn't identify token @" + _token + "@");
        buildNode(it->second);
    } while (_ss.good());
    return _token == end;
}