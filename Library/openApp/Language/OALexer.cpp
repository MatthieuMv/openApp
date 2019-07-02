/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OALexer
*/

// std::regex
#include <regex>

#include <openApp/Types/Error.hpp>
#include <openApp/Types/FStream.hpp>
#include <openApp/Types/SStream.hpp>
#include <openApp/Containers/Pair.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Language/OALexer.hpp>
#include <openApp/Language/Operator.hpp>

static constexpr auto ItemMatch = "[[:upper:]][[:alnum:]]*";
static constexpr auto PropertyMatch = "[[:alpha:]][[:alnum:]]*:";

void oA::Lang::OALexer::ProcessFile(const String &path, OANode &target)
{
    IFStream ss(path);

    if (!ss.good())
        throw AccessError("Lexer", "Invalid path @" + path + "@");
    OALexer(ss, target).processUnit();
}

void oA::Lang::OALexer::ProcessString(const String &string, OANode &target)
{
    ISStream ss(string);

    OALexer(ss, target).processUnit();
}

void oA::Lang::OALexer::ProcessExpression(const String &expr, Vector<String> &target)
{
    String word;
    const auto pushWord = [&word, &target] { target.emplace_back().swap(word); };

    for (auto c : expr) {
        if (std::isspace(c) && !word.empty()) {
            pushWord();
            continue;
        } else if (IsOperator(c) && !word.empty()) {
            if (IsOperator(word) && !IsOperator(word += c))
                word.pop_back();
            if (word == "++" || word == "--")
                continue;
            pushWord();
        }
        word.push_back(c);
    }
    pushWord();
}

static const oA::Vector<oA::Pair<std::regex, oA::Lang::OANode::Type>> LexMatches = {
    { std::regex("import", std::regex::optimize),       oA::Lang::OANode::ImportNode   },
    { std::regex(ItemMatch, std::regex::optimize),      oA::Lang::OANode::ItemNode     },
    { std::regex(PropertyMatch, std::regex::optimize),  oA::Lang::OANode::AssignNode   },
    { std::regex("property", std::regex::optimize),     oA::Lang::OANode::PropertyNode },
    { std::regex("function", std::regex::optimize),     oA::Lang::OANode::FunctionNode },
    { std::regex("on", std::regex::optimize),           oA::Lang::OANode::EventNode    }
};

void oA::Lang::OALexer::interpretToken(void)
{
    for (const auto &pair : LexMatches) {
        if (std::regex_match(token(), pair.first))
            return buildNode(pair.second);
    }
    throw LogicError("OALexer", "Can't interpret token @" + token() + "@");
}

void oA::Lang::OALexer::buildNode(OANode::Type type)
{
    static const oA::UMap<OANode::Type, void(OALexer::*)(void)> Builders = {
        { OANode::ImportNode,       &OALexer::buildImportNode },
        { OANode::ItemNode,         &OALexer::buildItemNode },
        { OANode::AssignNode,       &OALexer::buildAssignNode },
        { OANode::PropertyNode,     &OALexer::buildPropertyNode },
        { OANode::FunctionNode,     &OALexer::buildFunctionNode },
        { OANode::EventNode,        &OALexer::buildEventNode }
    };
    auto it = Builders.find(type);
    auto *root = _target;

    _target = &_target->childs.emplace_back();
    _target->type = type;
    (this->*it->second)();
    _target = root;
}

void oA::Lang::OALexer::buildImportNode(void)
{
    if (!readToken())
        throw LogicError("OALexer", "Excepted token @DirPath@ after @import@");
    pushToken();
}

void oA::Lang::OALexer::buildItemNode(void)
{
    pushToken();
    if (!readToken() || token() != "{")
        throw LogicError("OALexer", "Excepted token @{@ after @" + _target->args[0] + "@ declaration");
    processUnit("}");
}

void oA::Lang::OALexer::buildAssignNode(void)
{
    token().pop_back();
    pushToken();
    captureExpression();
    ProcessExpression(token(), _target->args);
}

void oA::Lang::OALexer::buildPropertyNode(void)
{
    if (!readToken() || token().back() != ':')
        throw LogicError("OALexer", "Unexcepted token @" + token() + "@ after @property@ declaration");
    buildAssignNode();
}

void oA::Lang::OALexer::buildFunctionNode(void)
{
    if (!readToken() || token().back() != ':')
        throw LogicError("OALexer", "Unexcepted token @" + token() + "@ after @function@ declaration");
    buildAssignNode();
}

void oA::Lang::OALexer::buildEventNode(void)
{
    if (!readToken() || token().back() != ':')
        throw LogicError("OALexer", "Unexcepted token @" + token() + "@ after @event@ declaration");
    buildAssignNode();
}