/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Parser
*/

#pragma once

// IFStream
#include "Core/FStream.hpp"
// Function
#include "Core/Function.hpp"
// UMap
#include "Core/UMap.hpp"
// Log
#include "Core/Log.hpp"
// List
#include "Core/List.hpp"
// ItemPtr
#include "App/Item.hpp"

namespace oA { class Parser; }

class oA::Parser
{
    /* Parser Context (used in a Stack to prevent memory overhead in recursive algorithm)
        root : Item context
        path : file path context
    */
    struct Context
    {
        Context(void) = default;
        Context(const String &filename) : path(filename) {}

        String path; // Context file path
        ItemPtr root; // Context item
        List<String> imports; // Context import paths
    };

    struct Unassigned
    {
        ItemPtr item;
        String property;
        String expression;
    };

    using ContextFct = Function<void(void)>;
    using ContextMatches = List<Pair<String, ContextFct>>;

public:
    /* Global static parser */
    static ItemPtr ParseFile(const String &path, bool verbose = false);

private:
    ContextMatches _matches; // Regex token matches
    List<Context> _contexts; // Context stack
    UMap<String, IFStream> _ifstreams; // FileStream stack
    String _token; // Temporary buffer (avoid stack overflow in recursion)
    mutable Log _log; // Custom parsing logger (can be disabled for speed)
    Uint _indent = 0; // Log indentation
    List<Unassigned> _unassigned; // Unassigned properties

    Parser(bool verbose = false);

    /* Matches */
    void addMatchFct(const String &match, void(Parser::*fct)(void)) { _matches.emplace_back(MakePair(match, std::bind(fct, this))); }

    /* Log helper */
    Char tab(void) const noexcept { _log << repeat(_indent) << '\t'; return 0; }

    /* Context stack access */
    inline Context &ctx(void) noexcept { return (_contexts.back()); }
    inline const Context &ctx(void) const noexcept { return (_contexts.back()); }
    inline IFStream &fs(void) noexcept { return (_ifstreams[ctx().path]); }

    /* Parsing loop */
    ItemPtr parseFile(const String &path);
    void parseUntil(const String &except = String());
    void parseToken(void);

    /* Resolve */
    void resolveUnassigned(void);

    /* Input Utils */
    bool readToken(void);
    bool readLine(Char delim = '\n');

    /* Regex expression matcher */
    bool match(const String &expr, const String &token);

    /* Context parsing functions */
    // Import
    void parseImport(void);
    bool resolveImportPath(String &path) const noexcept;
    // Item (Root && Childs)
    void parseItem(void);
    void parseRootItem(const String &type);
    void parseChildItem(const String &type);
    ItemPtr resolveType(const String &type);
    String getContextName(void) const noexcept;
    String getContextPath(void) const noexcept;
    bool resolveImportType(const String &type, String &path) const noexcept;
    // Properties
    void parseNewProperty(void);
    void parseProperty(void);
    // Special properties
    void parseItemId(void);
    void parseRelativePos(void);
    void parseRelativeSize(void);
    void parseCenter(void);
};