/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

#include <openApp/Types/Error.hpp>
#include <openApp/Language/Lexer.hpp>

void oA::Lang::Lexer::processUnit(const String &end)
{
    while (readToken() && token() != end)
        interpretToken();
    if (!end.empty() && token() != end)
        throw LogicError("Lexer", "Couldn't reach end of unit token @" + end + "@");
}

void oA::Lang::Lexer::captureExpression(void)
{
    char c = 0;

    for (c = _ss.get(); c && std::isspace(c) && c != '\n'; c = _ss.get());
    if (c == '\n')
        return;
    else if (c == '{') {
        _token.clear();
        do {
            if (!GetLine(_ss, _token, '}'))
                break;
        } while (!matchBrackets());
    } else {
        String tmp;
        _token.push_back(c);
        GetLine(_ss, tmp);
        _token += tmp;
    }
}

bool oA::Lang::Lexer::matchBrackets(void) const noexcept
{
    auto groups = 0;

    for (auto c : _token) {
        if (c == '{')
            ++groups;
        else if (c == '}')
            --groups;
    }
    return groups == 0;
}