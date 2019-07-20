/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ShuntingYard
*/

#pragma once

#include <openApp/App/Item.hpp>
#include <openApp/Language/Lexer.hpp>
#include <openApp/Language/Nodes/ExpressionGroupNode.hpp>
#include <openApp/Language/Operator.hpp>

namespace oA::Lang { class ShuntingYard; }

class oA::Lang::ShuntingYard
{
public:
    /**
     * @brief Tell the building mode of ShuntingYard algorithm
     */
    enum Mode {
        Expression,
        Function,
        Event
    };

    /**
     * @brief Internal parsing states
     */
    struct State
    {
        Int inLoop, inSwitch, inCondition;
    };

    /**
     * @brief Process a list of token representing an expression
     * 
     * @param root Root Item
     * @param tokens List of tokens
     * @param context Context of the tokens
     */
    static void ProcessTokenList(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context = "Root");

private:
    Vector<ASTNodePtr> _stack;
    Vector<ASTNodePtr> _opStack;
    ASTNodePtr _expr;
    State _state;
    Item &_root;
    const Lexer::TokenList &_tokens;
    const String &_context;
    const String &_name;
    Mode _mode;
    Int _line = 0;

    /**
     * @brief Construct a new Shunting Yard object
     * 
     * @param root Root item
     * @param tokens Token list
     * @param context Context of the tokens
     */
    ShuntingYard(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context);

    /**
     * @brief Process internal tokens, and convert them to an AST tree
     */
    void process(void);

    /**
     * @brief Process a single token and perform operation on the stack
     * 
     * @param it Token iterator
     */
    void processToken(Lexer::TokenList::const_iterator &it, ASTNode &root);

    void processOperator(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void processOperatorLogic(const OperatorModel &model);
    void processIncrementOperator(Lexer::TokenList::const_iterator &it);

    void processReference(Lexer::TokenList::const_iterator &it);
    ASTNodePtr findReference(const String &name, Int line);

    void processValue(Lexer::TokenList::const_iterator &it);
    void parseValue(Lexer::TokenList::const_iterator &it, Var &var);
    void parseValue(const String &value, Var &var, Int line);
    void parseContainerValue(Lexer::TokenList::const_iterator &it, Var &var);

    void processStatement(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseIf(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseElse(Lexer::TokenList::const_iterator &it, ASTNode &root);

    void parseSwitch(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseCase(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseCaseName(Lexer::TokenList::const_iterator &it, ASTNode &root);

    void parseWhile(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseFor(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseBreak(Lexer::TokenList::const_iterator &it);
    void parseReturn(Lexer::TokenList::const_iterator &it);

    void collectExpressionGroup(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root, const String &end);

    /**
     * @brief Build a tree out of current stack state
     * 
     * @param root Root node in which the node will be added
     */
    void buildStack(ASTNode &root);

    void buildOperator(Vector<ASTNodePtr>::iterator &it);

    bool peekStackArguments(Vector<ASTNodePtr>::iterator &it, ASTNode &target, Uint args) noexcept;

    /**
     * @brief Pop every operator of opStack and push them into the stack
     */
    void popOpStack(void) noexcept;

    /**
     * @brief Pop every operator of opStack and push them into the stack
     * 
     * @param end End marker operator
     */
    void popOpStack(Operator end, Int line);

    /**
     * @brief Build an error context String object
     * 
     * @param line Line which triggered the error
     * @return String Resulting error message
     */
    String getErrorContext(Int line) const noexcept { return " | @" + _context + "@ line #" + ToString(line) + "#"; }

    /**
     * @brief Get locals of root expr
     * 
     * @return UMap<String, Var>& Locals
     */
    UMap<String, Var> &locals(void) { return dynamic_cast<ExpressionGroupNode &>(*_expr).locals; }

    /**
     * @brief Assert that stacks are empty
     * 
     * @return true Stack and Operator stack are empty
     * @return false A stack is not empty
     */
    bool assertEmptyStack(void) const noexcept { return _stack.empty() && _opStack.empty(); }

    /**
     * @brief Build target expression
     */
    void buildTarget(void);
};