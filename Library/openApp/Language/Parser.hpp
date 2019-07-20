/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Parser
*/

#pragma once

#include <openApp/Types/String.hpp>
#include <openApp/Language/ASTNode.hpp>
#include <openApp/Language/Lexer.hpp>

namespace oA::Lang { class Parser; }

class oA::Lang::Parser
{
public:
    /**
     * @brief Parse a file and fill an Abstract Syntax Tree
     * 
     * @param path File path
     * @param tree Target tree
     * @return ASTNodePtr Resulting AST Tree
     */
    static ASTNodePtr ParseFile(const String &path);

    /**
     * @brief Parse a string and fill an Abstract Syntax Tree
     * 
     * @param string String to parse
     * @param context String context (equal to filename)
     * @return ASTNodePtr Resulting AST Tree
     */
    static ASTNodePtr ParseString(const String &string, const String &context = "Root");

private:
    ASTNodePtr _root;
    const String &_context;
    Lexer::TokenList &_tokens;

    /**
     * @brief Construct a new Parser object
     * 
     * @param context Item context (path)
     * @param tokens 
     */
    Parser(const String &context, Lexer::TokenList &tokens);

    /**
     * @brief Start the parsing operator on internal tokens
     * 
     * @return ASTNodePtr Resulting tree root node
     */
    ASTNodePtr parse(void);

    /**
     * @brief Parse a single token of internal list
     * 
     * @param parent Context node
     * @param it Token Iterator
     */
    void parseToken(ASTNodePtr &parent, Lexer::TokenList::iterator &it);

    /**
     * @brief Parse an import statement
     * 
     * @param parent Context node
     * @param it Token iterator
     */
    void parseImport(ASTNodePtr &parent, Lexer::TokenList::iterator &it);


    /**
     * @brief Parse a class declaration
     * 
     * @param parent Context node
     * @param it Token iterator
     */
    void parseClass(ASTNodePtr &parent, Lexer::TokenList::iterator &it);

    /**
     * @brief Parse a declaration statement
     * 
     * @param parent Context node
     * @param it Token iterator
     */
    void parseDeclaration(ASTNodePtr &parent, Lexer::TokenList::iterator &it);

    /**
     * @brief Parse an assignment statement
     * 
     * @param parent Context node
     * @param it Token iterator
     */
    void parseAssignment(ASTNodePtr &parent, Lexer::TokenList::iterator &it);

    /**
     * @brief Collect internal token of an expression (either group or not)
     * 
     * @param it Token iterator
     * @param target Target token list
     */
    void collectExpression(Lexer::TokenList::iterator &it, Lexer::TokenList &target);

    /**
     * @brief Collect internal token of an expression group (starting with the token after delimiter)
     * 
     * @param it Token iterator
     * @param target Target token list
     */
    void collectExpressionGroup(Lexer::TokenList::iterator &it, Lexer::TokenList &target);

    /**
     * @brief Get the Error Context object
     * 
     * @param line Line of the error
     * @return String Error message
     */
    String getErrorContext(Int line) const noexcept { return " | @" + _context + "@ line #" + ToString(line) + "#"; }
};