/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

#pragma once

#include <openApp/Types/String.hpp>
#include <openApp/Types/Stream.hpp>
#include <openApp/Language/Tree.hpp>

namespace oA { class Lexer; }

class oA::Lexer
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

    struct LexNode
    {
        Vector<String> data;
        TokenType type = Root;
    };

    using LexTree = Tree<LexNode>;

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
    IStream &_ss;

    Lexer(IStream &stream);

    bool process(LexTree &target, const String &end = String());
    void buildNode(LexTree &target, const String &token, TokenType type);
    void buildImport(LexTree &target, const String &token);
    void buildNewItem(LexTree &target, const String &token);
    void buildNewProperty(LexTree &target, const String &token);
    void buildPropertyAssign(LexTree &target, const String &token);
    void buildNewFunction(LexTree &target, const String &token);
    void buildNewEvent(LexTree &target, const String &token);

    void captureExpression(String &target);
};