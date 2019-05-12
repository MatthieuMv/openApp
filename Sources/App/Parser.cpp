/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Parser
*/

// std::regex
#include <regex>

// DirExists
#include <Core/Path.hpp>
// Parser
#include "App/Parser.hpp"
// AppFactory
#include "App/AppFactory.hpp"

static const oA::String C_PROPERTY_MATCH = "[A-Za-z]+[:]";
static const oA::String C_ITEM_MATCH = "[A-Z][A-Za-z]*";

oA::ItemPtr oA::Parser::ParseFile(const String &path, bool verbose)
{
    oA::AppFactory::RegisterBaseItems();
    return Parser(verbose).parseFile(path);
}

oA::Parser::Parser(bool verbose)
     : _log(oA::Log::COUT, oA::CSL_LIGHT_GRAY, oA::CSL_LIGHT_GREEN, oA::CSL_LIGHT_YELLOW)
{
    _log.setEnabled(verbose);
    _matches[C_ITEM_MATCH] = std::bind(&Parser::parseItem, this); // Item definition
    _matches[C_PROPERTY_MATCH] = std::bind(&Parser::parseProperty, this); // Existing Property
    _matches["import"] = std::bind(&Parser::parseImport, this); // Directory import
    _matches["property"] = std::bind(&Parser::parseNewProperty, this); // New property
    _matches["id:"] = std::bind(&Parser::parseItemId, this); // New property
}

oA::ItemPtr oA::Parser::parseFile(const String &path)
{
    ItemPtr root;

    _contexts.emplace_back(path);
    _ifstreams.emplace_back(path);
    if (!fs().good())
        throw AccessError("Parser", "Couldn't open file @" + path + "@");
    parseUntil();
    root.swap(ctx().root);
    _contexts.pop_back();
    _ifstreams.pop_back();
    return root;
}

void oA::Parser::parseUntil(const String &except)
{
    while (readToken() && _token != except)
        parseToken();
}

void oA::Parser::parseToken(void)
{
    for (auto &expr : _matches) {
        if (match(expr.first, _token))
            return expr.second();
    }
    throw SyntaxError("Parser", "Couldn't parse token @" + _token + "@ #(" + ctx().path + ")#");
}

bool oA::Parser::readToken(void)
{
    if (!fs().good() || !(fs() >> _token))
        return false;
    if (_token == "//") {
        readLine();
        return readToken();
    }
    return true;
}

bool oA::Parser::readLine(Char delim)
{
    if (!std::getline(fs(), _token, delim))
        return false;
    while (!_token.empty() && std::isspace(_token.front()))
        _token.erase(_token.begin());
    while (!_token.empty() && std::isspace(_token.back()))
        _token.pop_back();
    return true;
}

bool oA::Parser::match(const String &expr, const String &token)
{
    return std::regex_match(token, std::regex(expr));
}

void oA::Parser::parseImport(void)
{
    if (!readLine())
        throw AccessError("Parser", "Expected symbol @dirname@ after token @import@ #(" + ctx().path + ")#");
    if (!Path::DirExists(_token))
        throw AccessError("Parser", "Couldn't find directory to import @" + _token + "@ #(" + ctx().path + ")#");
    ctx().imports.push_back(_token);
}

void oA::Parser::parseItem(void)
{
    auto type = _token;

    if (!readToken() || _token != "{")
        throw SyntaxError("Parser", "Expected symbol @{@ after token @" + type + "@ #(" + ctx().path + ")#");
    if (!ctx().root)
        parseRootItem(type);
    else
        parseChildItem(type);
}

void oA::Parser::parseRootItem(const String &type)
{
    _log << tab() << "Instancing root item @" + type + "@" << endl;
    ctx().root = resolveType(type);
    ++_indent;
    parseUntil("}");
    if (readToken())
        throw LogicError("Parser", "Unexpected token @" + _token + "@ (#" + ctx().path + "#)");
    --_indent;
}

void oA::Parser::parseChildItem(const String &type)
{
    auto &rootCtx = ctx();

    _log << tab() << "Instancing child item @" + type + "@" << endl;
    ++_indent;
    _contexts.emplace_back();
    _contexts.back().path = rootCtx.path;
    _contexts.back().imports = rootCtx.imports;
    ctx().root = resolveType(type);
    rootCtx.root->addChild(ctx().root);
    parseUntil("}");
    _contexts.pop_back();
    --_indent;
}

oA::ItemPtr oA::Parser::resolveType(const String &type)
{
    String path;

    if (getContextName() != type && resolveImportType(type, path))
        return parseFile(path);
    if (oA::AppFactory::Exists(type))
        return oA::AppFactory::Instanciate(type);
    throw SyntaxError("Parser", "Couldn't find item type @" + type + "@ (#" + ctx().path + "#)");
}

oA::String oA::Parser::getContextName(void) const noexcept
{
    String res = ctx().path;
    auto pos = res.find_last_of('/');

    if (pos != res.npos)
        res.erase(0, pos);
    pos = res.find_last_of('.');
    if (pos != res.npos)
        res.erase(pos);
    return res;
}

bool oA::Parser::resolveImportType(const String &type, String &path) const noexcept
{
    for (String p : ctx().imports) {
        if (p.back() != '/')
            p.push_back('/');
        p += type + ".oA";
        if (Path::FileExists(p)) {
            path.swap(p);
            return true;
        }
    }
    return false;
}

void oA::Parser::parseNewProperty(void)
{
    String name;

    if (!readToken() || !match(C_PROPERTY_MATCH, _token))
        throw SyntaxError("Parser", "Expecting symbol @name:@ after keyword @property@ (#" + ctx().path + "#)");
    if (!ctx().root)
        throw LogicError("Parser", "Property @" + name + "@ must be in item definition (#" + ctx().path + "#)");
    name = _token;
    name.pop_back();
    _log << tab() << "Adding new property #" + _token + "#" << endl;
    if (_token.back() == ':')
        _token.pop_back();
    ctx().root->append(_token);
    parseProperty();
}

void oA::Parser::parseProperty(void)
{
    String name = _token;

    if (name.back() == ':')
        name.pop_back();
    if (!ctx().root)
        throw LogicError("Parser", "Property @" + name + "@ must be in item definition (#" + ctx().path + "#)");
    if (!readLine())
        throw SyntaxError("Parser", "Expecting @expression@ after symbol @" + name + "@ (#" + ctx().path + "#)");
    ctx().root->makeExpression(name, _token);
    _log << tab() << "Property #" + name + "# set to " << _token << endl;
}

void oA::Parser::parseItemId(void)
{
    if (!readToken())
        throw SyntaxError("Parser", "Expecting @expression@ after symbol @id@ (#" + ctx().path + "#)");
    ctx().root->get("id") = _token;
    _log << tab() << "Property #id# set to " + ctx().root->get("id")->getConst<String>() << endl;
}