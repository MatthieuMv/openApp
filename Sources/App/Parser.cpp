/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Parser
*/

// std::regex
#include <regex>

// DirExists
#include "Core/Path.hpp"
// Parser
#include "App/Parser.hpp"
// AppFactory
#include "App/AppFactory.hpp"

static const oA::String C_PROPERTY_MATCH = "[A-Za-z]+[:]";
static const oA::String C_ITEM_MATCH = "[A-Z][A-Za-z]*";

oA::ItemPtr oA::Parser::ParseFile(const String &path, bool verbose)
{
    Parser p(verbose);

    oA::AppFactory::RegisterBaseItems();
    auto itm = p.parseFile(path);
    p.resolveUnassigned();
    return itm;
}

oA::Parser::Parser(bool verbose)
     : _log(oA::Log::Stdout, oA::CSL_LIGHT_GRAY, oA::CSL_LIGHT_GREEN, oA::CSL_LIGHT_YELLOW)
{
    _log.setEnabled(verbose);
    addMatchFct("import", &Parser::parseImport); // Directory import
    addMatchFct("property", &Parser::parseNewProperty); // New property
    addMatchFct("id:", &Parser::parseItemId); // Item id
    addMatchFct("relativePos:", &Parser::parseRelativePos); // Relative pos
    addMatchFct("relativeSize:", &Parser::parseRelativeSize); // Relative size
    addMatchFct("center:", &Parser::parseCenter); // Relative size
    addMatchFct(C_ITEM_MATCH, &Parser::parseItem); // Item definition
    addMatchFct(C_PROPERTY_MATCH, &Parser::parseProperty); // Existing Property
}

oA::ItemPtr oA::Parser::parseFile(const String &path)
{
    ItemPtr root;

    _contexts.emplace_back(path);
    if (_ifstreams.find(path) == _ifstreams.end())
        _ifstreams.insert(MakePair(path, path));
    else
        _ifstreams[path].seekg(0, std::ios::beg);
    if (!fs().good())
        throw AccessError("Parser", "Couldn't access file @" + path + "@");
    parseUntil();
    root.swap(ctx().root);
    _contexts.pop_back();
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

void oA::Parser::resolveUnassigned(void)
{
    for (auto &u : _unassigned) {
        u.item->makeExpression(u.property, u.expression);
    }
    _unassigned.clear();
}

bool oA::Parser::readToken(void)
{
    if (!fs().good() || !(fs() >> _token))
        return false;
    if (_token == "//") {
        readLine();
        return readToken();
    } else if (_token == "/*") {
        while (readToken() && _token != "*/");
        return readToken();
    }
    return true;
}

bool oA::Parser::readLine(Char delim)
{
    if (!std::getline(fs(), _token, delim))
        return false;
    auto comment = _token.find("//");
    if (comment != _token.npos)
        _token.erase(comment);
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
    if (!resolveImportPath(_token))
        throw AccessError("Parser", "Couldn't find directory to import @" + _token + "@ #(" + ctx().path + ")#");
    ctx().imports.push_back(_token);
}

bool oA::Parser::resolveImportPath(String &path) const noexcept
{
    String tmp;

    if (Path::DirExists(path))
        return true;
    tmp = tmp = getContextPath() + path;
    if (Path::DirExists(tmp)) {
        path.swap(tmp);
        return true;
    }
    return false;
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
        res.erase(0, pos + 1);
    pos = res.find_last_of('.');
    if (pos != res.npos)
        res.erase(pos);
    return res;
}

oA::String oA::Parser::getContextPath(void) const noexcept
{
    String res = ctx().path;
    auto pos = res.find_last_of('/');

    if (pos == res.npos)
        return String();
    res.erase(pos + 1);
    return res;
}

bool oA::Parser::resolveImportType(const String &type, String &path) const noexcept
{
    String tmp = getContextPath() + type +".oA";

    if (Path::FileExists(tmp)) {
        path.swap(tmp);
        return true;
    }
    for (const String &p : ctx().imports) {
        tmp = p;
        if (tmp.back() != '/')
            tmp.push_back('/');
        tmp += type + ".oA";
        if (Path::FileExists(tmp)) {
            path.swap(tmp);
            return true;
        }
    }
    return false;
}

void oA::Parser::parseNewProperty(void)
{
    String name;

    if (!ctx().root)
        throw LogicError("Parser", "Property @" + name + "@ must be in item definition (#" + ctx().path + "#)");
    if (!readToken() || !match(C_PROPERTY_MATCH, _token))
        throw SyntaxError("Parser", "Expecting symbol @name:@ after keyword @property@ (#" + ctx().path + "#)");
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

    if (!ctx().root)
        throw LogicError("Parser", "Property @" + name + "@ must be in item definition (#" + ctx().path + "#)");
    if (name.back() == ':')
        name.pop_back();
    if (!readLine())
        throw SyntaxError("Parser", "Expecting @expression@ after symbol @" + name + "@ (#" + ctx().path + "#)");
    try {
        ctx().root->makeExpression(name, _token);
        _log << tab() << "Property #" + name + "# set to " << _token << endl;
    } catch (...) {
        Unassigned unassigned;
        unassigned.item = ctx().root;
        unassigned.property.swap(name);
        unassigned.expression.swap(_token);
        _unassigned.push_back(unassigned);
    }
}

void oA::Parser::parseItemId(void)
{
    if (!ctx().root)
        throw LogicError("Parser", "Property @id@ must be in item definition (#" + ctx().path + "#)");
    if (!readToken())
        throw SyntaxError("Parser", "Expecting @expression@ after symbol @id@ (#" + ctx().path + "#)");
    ctx().root->get("id") = _token;
    _log << tab() << "Property #id# set to " + ctx().root->get("id")->getConst<String>() << endl;
}

void oA::Parser::parseRelativePos(void)
{
    String x, y;

    if (!ctx().root)
        throw LogicError("Parser", "Property @relativePos@ must be in item definition (#" + ctx().path + "#)");
    if (!readToken() || _token.back() != ',')
        throw SyntaxError("Parser", "Invalid relativePos @x@ token (#" + ctx().path + "#)");
    _token.pop_back();
    x.swap(_token);
    if (!readToken())
        throw SyntaxError("Parser", "Invalid relativePos @y@ token (#" + ctx().path + "#)");
    y.swap(_token);
    ctx().root->makeExpression("x", "parent.width * " + x + " - width / 2");
    ctx().root->makeExpression("y", "parent.height * " + y + " - height / 2");
}

void oA::Parser::parseRelativeSize(void)
{
    String width, height;

    if (!ctx().root)
        throw LogicError("Parser", "Property @relativeSize@ must be in item definition (#" + ctx().path + "#)");
    if (!readToken() || _token.back() != ',')
        throw SyntaxError("Parser", "Invalid relativeSize @x@ token (#" + ctx().path + "#)");
    _token.pop_back();
    width.swap(_token);
    if (!readToken())
        throw SyntaxError("Parser", "Invalid relativeSize @y@ token (#" + ctx().path + "#)");
    height.swap(_token);
    ctx().root->makeExpression("width", "parent.width * " + width);
    ctx().root->makeExpression("height", "parent.height * " + height);
}

void oA::Parser::parseCenter(void)
{
    String res;

    if (!ctx().root)
        throw LogicError("Parser", "Property @center@ must be in item definition (#" + ctx().path + "#)");
    if (!readToken() || !IsBoolean(_token))
        throw SyntaxError("Parser", "Can't interpret expression @center@ (#" + ctx().path + "#)");
    res = FromBoolean(_token) ? "true" : "false";
    ctx().root->makeExpression("hCenter", res);
    ctx().root->makeExpression("vCenter", res);
}