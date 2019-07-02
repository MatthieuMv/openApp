/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OALexer
*/

#pragma once

#include <openApp/Language/Lexer.hpp>
#include <openApp/Language/OANode.hpp>

namespace oA::Lang { class OALexer; }

class oA::Lang::OALexer : public Lexer
{
public:
    /**
     * @brief Build an openApp AST node from a file, capturing and lexing each expression
     * 
     * @param path File path
     * @param target AST Root node
     */
    static void ProcessFile(const String &path, OANode &target);

    /**
     * @brief Build an openApp AST node from a string, capturing and lexing each expression
     * 
     * @param string File string
     * @param target AST Root node
     */
    static void ProcessString(const String &string, OANode &target);
    
    /**
     * @brief Lex given expression and push tokens into target Vector
     * 
     * @param expr Expression to process
     * @param target Target Vector
     */
    static void ProcessExpression(const String &expr, Vector<String> &target);

private:
    OANode *_target;

    virtual ~OALexer(void) = default;
    OALexer(IStream &ss, OANode &target) : Lexer(ss), _target(&target) {}

    virtual void interpretToken(void);

    void buildNode(OANode::Type type);
    void buildImportNode(void);
    void buildItemNode(void);
    void buildAssignNode(void);
    void buildPropertyNode(void);
    void buildFunctionNode(void);
    void buildEventNode(void);

    void pushToken(void) { _target->args.emplace_back(std::move(_token)); }
};