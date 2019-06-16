/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

// std::regex
#include <regex>

#include <openApp/Types/Error.hpp>
#include <openApp/Types/SStream.hpp>
#include <openApp/Types/FStream.hpp>
#include <openApp/Types/Function.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Language/Lexer.hpp>

static constexpr auto ItemMatch = "[A-Z][a-zA-Z0-9]*";
static constexpr auto PropertyMatch = "[a-zA-Z][a-zA-Z0-9]*:";

void oA::Lexer::ProcessFile(const String &path, LexTree &target)
{
    IFStream ss(path);

    if (!ss.good())
        throw AccessError("Lexer", "Invalid path @" + path + "@");
    Lexer(ss).process(target);
}

void oA::Lexer::ProcessString(const String &toProcess, LexTree &target)
{
    ISStream ss(toProcess);

    target.childs.clear();
    Lexer(ss).process(target);
}

oA::Lexer::Lexer(IStream &stream) : _ss(stream)
{
}

bool oA::Lexer::process(LexTree &target, const String &end)
{
    static const oA::UMap<oA::String, oA::Lexer::TokenType> LexMatches = {
        { "import",       oA::Lexer::Import           },
        { ItemMatch,      oA::Lexer::NewItem          },
        { "property",     oA::Lexer::NewProperty      },
        { PropertyMatch,  oA::Lexer::PropertyAssign   },
        { "function",     oA::Lexer::NewFunction      },
        { "on",           oA::Lexer::NewEvent         }
    };
    String token;

    do {
        if (!_ss >> token || token == end)
            break;
        auto it = LexMatches.findIf([&token](const auto &m) { return std::regex_match(token, std::regex(m.first)); }));
        if (it == LexMatches.end())
            throw LogicError("Lexer", "Couldn't identify token @" + token + "@");
        buildNode(target, token, it->second);
    } while (_ss.good());
    return token == end;
}

void oA::Lexer::buildNode(LexTree &target, const String &token, TokenType type)
{
    static const UMap<Lexer::TokenType, void(Lexer::*)(LexTree &, const String &)> LexBuild = {
        { Import,           &Lexer::buildImport         },
        { NewItem,          &Lexer::buildNewItem        },
        { NewProperty,      &Lexer::buildNewProperty    },
        { PropertyAssign,   &Lexer::buildPropertyAssign },
        { NewFunction,      &Lexer::buildNewFunction    },
        { NewEvent,         &Lexer::buildNewEvent       }
    };
    auto it = LexBuild.find(type);

    if (it == LexBuild.end())
        throw LogicError("Lexer", "Invalid token type");
    auto &child = target.childs.emplace_back();
    child.value.type = type;
    (this->*it->second)(child, token);
}

void oA::Lexer::buildImport(LexTree &target, const String &)
{
    if (!(_ss >> target.value.data.emplace_back()))
        throw LogicError("Lexer", "Excepted @FolderPath@ after token @import@");
}

void oA::Lexer::buildNewItem(LexTree &target, const String &token)
{
    String tmp;

    if (!(_ss >> tmp) || tmp != '{')
        throw LogicError("Lexer", "Excepted @{@ after item declaration");
    target.value.data.emplace_back(token);
    if (!process(target, "}"))
        throw LogicError("Lexer", "Missing closing bracket of @" + token + "@");
}

void oA::Lexer::buildNewProperty(LexTree &target, const String &)
{
    String name;

    if (!(_ss >> name) || !std::regex_match(name, std::regex(PropertyMatch)))
        throw LogicError("Lexer", "Invalid property declaration @" + name + "@");
    buildPropertyAssign(target, name);
}

void oA::Lexer::buildPropertyAssign(LexTree &target, const String &name)
{
    target.value.data.emplace_back(name);
    captureExpression(target.value.data.emplace_back());
}

void oA::Lexer::buildNewFunction(LexTree &target, const String &)
{
    String name;

    if (!(_ss >> name) || !std::regex_match(name, std::regex(PropertyMatch)))
        throw LogicError("Lexer", "Invalid function declaration @" + name + "@");
    target.value.data.emplace_back(name);
    captureExpression(target.value.data.emplace_back());
}

void oA::Lexer::buildNewEvent(LexTree &target, const String &)
{
    String name;

    if (!(_ss >> name) || !std::regex_match(name, std::regex(PropertyMatch)))
        throw LogicError("Lexer", "Invalid event declaration @" + name + "@");
    target.value.data.emplace_back(name);
    captureExpression(target.value.data.emplace_back());
}

void oA::Lexer::captureExpression(String &target)
{
    if (!(_ss >> target))
        return;
    if (target == "{") {
        target.clear();
        std::getline(_ss, target, '}');
    } else
        std::getline(_ss, target);
}