
/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Parser
*/

// std::regex
#include <regex>

#include <openApp/Core/Path.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Language/Parser.hpp>
#include <openApp/Language/Nodes.hpp>

oA::Lang::ASTNodePtr oA::Lang::Parser::ParseFile(const String &path)
{
    Lexer::TokenList tokens;

    Lexer::ProcessFile(path, tokens);
    return Parser(path, tokens).parse();
}

oA::Lang::ASTNodePtr oA::Lang::Parser::ParseString(const String &string, const String &context)
{
    Lexer::TokenList tokens;

    Lexer::ProcessString(string, tokens, context);
    return Parser(context, tokens).parse();
}

oA::Lang::Parser::Parser(const String &context, Lexer::TokenList &tokens) : _context(context), _tokens(tokens)
{
}

oA::Lang::ASTNodePtr oA::Lang::Parser::parse(void)
{
    _root = std::make_unique<ASTNode>();
    for (auto it = _tokens.begin(); it != _tokens.end();) {
        parseToken(_root, it);
    }
    return std::move(_root);
}

static const std::regex NameMatch("([[:alpha:]][[:alnum:]]*)(.[[:alpha:]][[:alnum:]]*)*", std::regex::optimize);

void oA::Lang::Parser::parseToken(ASTNodePtr &parent, Lexer::TokenList::iterator &it)
{
    static const Vector<Pair<std::regex, void(Parser::*)(ASTNodePtr &, Lexer::TokenList::iterator &)>> FunctionMap = {
        { std::regex("import", std::regex::optimize),                       &Parser::parseImport        },
        { std::regex("property|function|on", std::regex::optimize),         &Parser::parseDeclaration   },
        { NameMatch,                                                        &Parser::parseName          }
    };
    auto match = FunctionMap.findIf([it](const auto &p) { return std::regex_match(it->first, p.first); });

    if (match == FunctionMap.end())
        throw LogicError("Parser", "Unexpected token @" + it->first + "@" + getErrorContext(it->second));
    (this->*match->second)(parent, it);
}

void oA::Lang::Parser::parseImport(ASTNodePtr &parent, Lexer::TokenList::iterator &it)
{
    auto line = it->second;

    if (++it == _tokens.end())
        throw LogicError("Parser", "Excepted directory path after token @import@" + getErrorContext(line));
    if (it->first.size() < 2 || it->first.front() != '\"' || it->first.back() != '\"')
        throw LogicError("Parser", "Invalid @import@ statement (directory path must be quoted)" + getErrorContext(it->second));
    it->first.pop_back();
    it->first.erase(0, 1);
    it->first.tryAppend("/");
    if (!Path::DirExists(it->first))
        throw AccessError("Parser", "Couldn't access imported directory @" + it->first + "@" + getErrorContext(it->second));
    parent->emplaceAs<ImportNode>(std::move(it->first), it->second);
    ++it;
}

void oA::Lang::Parser::parseName(ASTNodePtr &parent, Lexer::TokenList::iterator &it)
{
    auto line = it->second;
    auto tmp = it;

    if (++tmp == _tokens.end())
        throw LogicError("Parser", "Unexcpected end of @declaration@" + getErrorContext(line));
    if (tmp->first == ":")
        parseAssignment(parent, it);
    else
        parseClass(parent, it);
}

void oA::Lang::Parser::parseClass(ASTNodePtr &parent, Lexer::TokenList::iterator &it)
{
    auto line = it->second;
    String name = std::move(it->first);

    if (++it == _tokens.end() || it->first != "{")
        throw LogicError("Parser", "Excepted token @{@ after class declaration" + getErrorContext(line));
    ++it;
    parent->emplaceAs<ClassNode>(std::move(name), line);
    for (auto &node = parent->children.back(); it != _tokens.end() && it->first != "}";)
        parseToken(node, it);
    if (it == _tokens.end())
        throw LogicError("Parser", "Missing end of class definition token @}@" + getErrorContext(line));
    ++it;
}

static const oA::UMap<oA::String, oA::Lang::DeclarationNode::DeclarationType> Types = {
    { "property",   oA::Lang::DeclarationNode::PropertyDeclaration    },
    { "function",   oA::Lang::DeclarationNode::FunctionDeclaration    },
    { "on",         oA::Lang::DeclarationNode::EventDeclaration       }
};

void oA::Lang::Parser::parseDeclaration(ASTNodePtr &parent, Lexer::TokenList::iterator &it)
{
    auto line = it->second;
    auto type = Types.find(it->first);

    if (++it == _tokens.end() || type == Types.end() || !std::regex_match(it->first, NameMatch))
        throw LogicError("Parser", "Invalid @declaration@" + getErrorContext(line));
    auto name = it;
    if (++it == _tokens.end() || it->first != ":")
        throw LogicError("Parser", "Invalid @declaration@" + getErrorContext(line));
    auto &node = parent->emplaceAs<DeclarationNode>(std::move(name->first), type->second, line);
    collectExpression(++it, node.tokens);
}

void oA::Lang::Parser::parseAssignment(ASTNodePtr &parent, Lexer::TokenList::iterator &it)
{
    auto line = it->second;
    auto &node = parent->emplaceAs<DeclarationNode>(std::move(it->first), DeclarationNode::AssignmentDeclaration, line);

    if (++it == _tokens.end() || it->first != ":")
        throw LogicError("Parser", "Invalid @declaration@" + getErrorContext(line));
    collectExpression(++it, node.tokens);
}

void oA::Lang::Parser::collectExpression(Lexer::TokenList::iterator &it, Lexer::TokenList &target)
{
    auto line = it->second;

    if (it == _tokens.end())
        return;
    if (it->first == "{")
        return collectExpressionGroup(++it, target);
    for (; it != _tokens.end() && it->second == line; ++it) {
        target.emplace_back(std::move(it->first), it->second);
    }
}

void oA::Lang::Parser::collectExpressionGroup(Lexer::TokenList::iterator &it, Lexer::TokenList &target)
{
    auto firstLine = it->second;
    auto groupLevel = 1;

    for (; it != _tokens.end() && groupLevel; ++it) {
        if (it->first == "{")
            ++groupLevel;
        else if (it->first == "}")
            --groupLevel;
        if (!groupLevel)
            continue;
        target.emplace_back(std::move(it->first), it->second);
    }
    if (groupLevel > 0)
        throw LogicError("Parser", "Missing end of expression declaration token @}@" + getErrorContext(firstLine));
}