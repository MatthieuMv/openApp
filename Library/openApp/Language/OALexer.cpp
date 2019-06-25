/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OALexer
*/

// std::regex
#include <regex>

#include <openApp/Types/SStream.hpp>
#include <openApp/Types/FStream.hpp>
#include <openApp/Types/Function.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Language/OALexer.hpp>

static constexpr auto ItemMatch = "[A-Z][a-zA-Z0-9]*";
static constexpr auto PropertyMatch = "[a-zA-Z][a-zA-Z0-9]*:";

void oA::OALexer::ProcessFile(const String &path, LexTree &target)
{
    IFStream ss(path);

    if (!ss.good())
        throw AccessError("Lexer", "Invalid path @" + path + "@");
    OALexer(ss, target).process();
}

void oA::OALexer::ProcessString(const String &toProcess, LexTree &target)
{
    ISStream ss(toProcess);

    OALexer(ss, target).process();
}

bool oA::OALexer::process(const String &end)
{
    static const oA::UMap<String, oA::OALexer::TokenType> LexMatches = {
        { "import",       Import           },
        { ItemMatch,      NewItem          },
        { "property",     NewProperty      },
        { PropertyMatch,  PropertyAssign   },
        { "function",     NewFunction      },
        { "on",           NewEvent         }
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

void oA::OALexer::buildNode(TokenType type)
{
    static const UMap<TokenType, void(OALexer::*)(void)> LexBuild = {
        { Import,           &OALexer::buildImport         },
        { NewItem,          &OALexer::buildNewItem        },
        { NewProperty,      &OALexer::buildNewProperty    },
        { PropertyAssign,   &OALexer::buildPropertyAssign },
        { NewFunction,      &OALexer::buildNewFunction    },
        { NewEvent,         &OALexer::buildNewEvent       }
    };
    auto it = LexBuild.find(type);
    auto &child = _target->childs.emplace_back();
    auto *old = _target;

    child.value.type = type;
    _target = &child;
    (this->*it->second)();
    _target = old;
}

void oA::OALexer::buildImport(void)
{
    if (!(_ss >> _target->value.data.emplace_back()))
        throw LogicError("OALexer", "Excepted @FolderPath@ after token @import@");
}

void oA::OALexer::buildNewItem(void)
{
    String tmp;

    tmp.swap(_token);
    _target->value.data.emplace_back(tmp);
    if (!readToken() || _token != "{")
        throw LogicError("OALexer", "Excepted @{@ after item declaration");
    if (!process("}"))
        throw LogicError("OALexer", "Missing closing bracket of @" + tmp + "@");
}

void oA::OALexer::buildNewProperty(void)
{
    if (!readToken() || !std::regex_match(_token, std::regex(PropertyMatch)))
        throw LogicError("OALexer", "Invalid property declaration @" + _token + "@");
    buildPropertyAssign();
}

void oA::OALexer::buildPropertyAssign(void)
{
    _target->value.data.emplace_back(_token.substr(0, _token.length() - 1));
    captureExpression(_target->value.data.emplace_back());
}

void oA::OALexer::buildNewFunction(void)
{
    String &name = _target->value.data.emplace_back();

    if (!readToken(name) || !std::regex_match(name, std::regex(PropertyMatch)))
        throw LogicError("OALexer", "Invalid function declaration @" + name + "@");
    name.pop_back();
    captureExpression(_target->value.data.emplace_back());
}

void oA::OALexer::buildNewEvent(void)
{
    String &name = _target->value.data.emplace_back();

    if (!readToken(name) || !std::regex_match(name, std::regex(PropertyMatch)))
        throw LogicError("OALexer", "Invalid event declaration @" + name + "@");
    name.pop_back();
    captureExpression(_target->value.data.emplace_back());
}