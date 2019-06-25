/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OALexer
*/

#pragma once

#include <openApp/Language/Lexer.hpp>

namespace oA { class OALexer; class OANode; }

class oA::OALexer : protected Lexer<OANode>
{
public:
    enum TokenType {
        Root = 0,
        Import,
        NewItem,
        NewProperty,
        PropertyAssign,
        NewFunction,
        NewEvent
    };

    using Lexer<OANode>::LexTree;

    /**
     * @brief Process a file, storing the result in target LexTree
     *
     * @param path File path
     * @param target Target
     */
    static void ProcessFile(const String &path, LexTree &target);

    /**
     * @brief Process a string, storing the result in target LexTree
     *
     * @param toProcess String to process
     * @param target Target
     */
    static void ProcessString(const String &toProcess, LexTree &target);

private:
    using Lexer::Lexer;

    virtual ~OALexer(void) = default;

    virtual bool process(const String &end = String());

    void buildNode(TokenType type);
    void buildImport(void);
    void buildNewItem(void);
    void buildNewProperty(void);
    void buildPropertyAssign(void);
    void buildNewFunction(void);
    void buildNewEvent(void);
};

struct oA::OANode
{
    Vector<String> data;
    OALexer::TokenType type = OALexer::Root;
};
