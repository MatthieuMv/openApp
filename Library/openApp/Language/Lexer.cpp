/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

#include <openApp/Types/SStream.hpp>
#include <openApp/Types/FStream.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Core/GetLine.hpp>
#include <openApp/Core/Log.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Language/Lexer.hpp>
#include <openApp/Language/Operator.hpp>

void oA::Lang::Lexer::ProcessFile(const String &path, TokenList &tokens)
{
    IFStream stream(path);

    Lexer(path, stream, tokens).process();
}

void oA::Lang::Lexer::ProcessString(const String &string, TokenList &tokens, const String &context)
{
    ISStream stream(string);

    Lexer(context, stream, tokens).process();
}

void oA::Lang::Lexer::ShowTokenList(const TokenList &list)
{
    auto line = -1;
    auto tab = 0;
    auto count = 0;

    for (const auto &token : list) {
        char quote = IsOperator(token.first) ? '#' : '@';
        if (token.second > line) {
            line = token.second;
            if (count)
                cout << endl;
            cout << line << ": " << Repeat(tab) << "   ";
        }
        cout << quote << token.first << quote << ' ';
        if (token.first == "{")
            ++tab;
        else if (token.first == "}")
            --tab;
        ++count;
    }
    cout << endl;
}

oA::Lang::Lexer::Lexer(const String &context, IStream &stream, TokenList &tokens)
    : _context(context), _ss(stream), _tokens(tokens)
{
    if (!stream.good())
        throw AccessError("Lexer", "Can't access file @" + context + "@");
}

void oA::Lang::Lexer::process(void)
{
    for (char c = get(); c > 0; c = get()) {
        processChar(c);
    }
}

void oA::Lang::Lexer::processChar(char c)
{
    if (std::isspace(c))
        return;
    else if (std::isalpha(c))
        processWord(c);
    else if (std::isdigit(c) || c == '.')
        processNumber(c);
    else if (c == '\"')
        processString(c);
    else if (c == '/' && peek() == '/')
        processComment(false);
    else if (c == '/' && peek() == '*')
        processComment(true);
    else if (IsOperator(c))
        processOperator(c);
}

void oA::Lang::Lexer::processString(String &&res)
{
    auto line = _line;
    char c;

    for (c = get(); c > 0 && c != '"'; c = get()) {
        if (c == '\\' && peek() == '"')
            res.push_back(get());
        else
            res.push_back(c);
    }
    if (c != '"')
        throw LogicError("Lexer", "Missing end of string token @\"@" + getErrorContext(line));
    res.push_back(c);
    pushToken(std::move(res));
}

void oA::Lang::Lexer::processNumber(String &&res)
{
    bool hasDot = res.front() == '.';
    auto line = _line;
    char c;

    for (c = peek(); c > 0; c = peek()) {
        if (c == '.') {
            if (hasDot)
                throw LogicError("Lexer", "Invalid decimal @" + (res += c) + "@" + getErrorContext(line));
            hasDot = true;
        } else if (!std::isdigit(c))
            break;
        res.push_back(get());
    }
    pushToken(std::move(res));
}

void oA::Lang::Lexer::processComment(bool multiline)
{
    auto line = _line;

    if (!multiline) {
        String cache;
        GetLine(_ss, cache);
        ++_line;
        return;
    }
    for (char c = get(); c > 0; c = get()) {
        if (c == '*' && peek() == '/') {
            get();
            return;
        }
    }
    throw LogicError("Lexer", "Missing end of comment token @*/@" + getErrorContext(line));
}

void oA::Lang::Lexer::processOperator(String &&res)
{
    char c = peek();

    if (!IsOperator(c))
        return pushToken(std::move(res));
    res.push_back(peek());
    if (res == "++" || res == "--") {
        get();
        return processIncrement(res);
    }
    if (IsOperator(res)) {
        get();
        return processOperator(std::move(res));
    }
    res.pop_back();
    pushToken(std::move(res));
}

void oA::Lang::Lexer::processIncrement(String &res)
{
    if (std::isalpha(peek()))
        processWord(std::move(res));
    else if (std::isalpha(_tokens.back().first))
        _tokens.back().first.append(res);
    else
        throw LogicError("Lexer", "Invalid operator @" + res + "@" + getErrorContext());
}

void oA::Lang::Lexer::processWord(String &&res)
{
    char c;

    for (c = peek(); std::isalnum(c) || c == '.'; c = peek())
        res.push_back(get());
    pushToken(std::move(res));
    switch (c) {
    case '(':
        return processFunctionCall(get());
    case '[':
        return processIndexAccess(get());
    default:
        break;
    }
}

void oA::Lang::Lexer::processFunctionCall(String &&res)
{
    if (peek() == ')') {
        res.push_back(get());
        pushToken(std::move(res));
        return;
    }
    res.push_back('(');
    pushToken(std::move(res));
    processFunctionArgs();
}

void oA::Lang::Lexer::processFunctionArgs(void)
{
    auto opened = 1;
    auto line = _line;

    for (char c = get(); c > 0; c = get()) {
        if (c == '(')
            ++opened;
        else if (c == ')')
            --opened;
        if (!opened)
            break;
        processChar(c);
    }
    if (opened)
        throw LogicError("Lexer", "Invalid @function call@" + getErrorContext(line));
    pushToken("))");
}

void oA::Lang::Lexer::processIndexAccess(String &&res)
{
    res.push_back(']');
    pushToken(std::move(res));
    for (char c = get(); c > 0; c = get()) {
        if (std::isspace(c))
            continue;
        if (c == ']')
            break;
        processChar(c);
    }
    pushToken(std::move(res));
}