/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ShuntingYard
*/

#pragma once

#include <openApp/Items/Item.hpp>
#include <openApp/Language/Lexer.hpp>
#include <openApp/Language/Nodes/ExpressionGroupNode.hpp>
#include <openApp/Language/Operator.hpp>
#include <openApp/Language/Function.hpp>

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
        Int inLoop = 0, inSwitch = 0, inCondition = 0;
    };

    /**
     * @brief Process a string representing an expression
     *
     * @param root Root Item
     * @param name Expression name
     * @param expr Expression string
     * @param mode ShuntingYard mode
     * @param context Context of the tokens
     */
    static void ProcessString(Item &root, const String &name, const String &expr, Mode mode, const String &context = "Root", bool verbose = false, UInt tab = 0);

    /**
     * @brief Process a list of token representing an expression
     *
     * @param root Root Item
     * @param name Expression name
     * @param mode ShuntingYard mode
     * @param tokens List of tokens
     * @param context Context of the tokens
     */
    static void ProcessTokenList(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context = "Root", bool verbose = false, UInt tab = 0);

private:
    Vector<ASTNodePtr> _stack, _opStack;
    ASTNodePtr _expr;
    PropertyPtr _target;
    State _state;
    Item &_root;
    const Lexer::TokenList &_tokens;
    const String &_context;
    const String &_name;
    Mode _mode;
    Int _line = 0;
    UInt _tab = 0;
    ASTNode::NodeType _lastType = ASTNode::Root;
    Operator _lastOp = Operator::Addition;
    bool _verbose = false;

    /**
     * @brief Construct a new Shunting Yard object
     *
     * @param root Root item
     * @param tokens Token list
     * @param context Context of the tokens
     */
    ShuntingYard(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context, bool verbose, UInt tab);

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

    /**
     * @brief Push a OperatorNode to the _opStack, setting the variable _lastType
     *
     * @param type OperatorNode's type
     * @return ASTNodePtr& Inserted node
     */
    ASTNodePtr &pushToOpStack(Operator type);

    /**
     * @brief Push an ASTNode to the _stack, setting the variable _lastType
     *
     * @param ptr ASTNode pointer
     * @return ASTNodePtr& Inserted node
     */
    ASTNodePtr &pushToStack(ASTNodePtr &&ptr);

    void processOperator(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void processOperatorLogic(const OperatorModel &model);
    void processSubstractionOperator(const OperatorModel &model);
    void processIncrementOperator(Lexer::TokenList::const_iterator &it);

    void processName(Lexer::TokenList::const_iterator &it);
    void processReference(Lexer::TokenList::const_iterator &it);
    ASTNodePtr findReference(const String &name, Int line);
    void processFunction(Lexer::TokenList::const_iterator &it);
    void processFunction(Lexer::TokenList::const_iterator &it, const String &symbol, const String &object);
    void processFunctionArguments(Lexer::TokenList::const_iterator &it, ASTNode &root, const FunctionModel &model);
    void peekFunctionArguments(Lexer::TokenList::const_iterator &it, ASTNode &root);

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
    void parseDefault(Lexer::TokenList::const_iterator &it, ASTNode &root);

    void parseWhile(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseFor(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseBreak(Lexer::TokenList::const_iterator &it);
    void parseReturn(Lexer::TokenList::const_iterator &it);

    void parseVariable(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void parseStaticVariable(Lexer::TokenList::const_iterator &it);

    void collectExpressionGroup(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root);
    void collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root, const String &end);
    void collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root, const Vector<String> &ends);
    void collectSingleGroup(Lexer::TokenList::const_iterator &it, ASTNode &root);

    /**
     * @brief Build a tree out of current stack state
     *
     * @param root Root node in which the node will be added
     */
    void buildStack(ASTNode &root);

    /**
     * @brief Build operator
     *
     * @param it Stack iterator
     */
    void buildOperator(Vector<ASTNodePtr>::iterator &it);

    /**
     * @brief Peek argument from stack
     *
     * @param it Stack iterator
     * @param target Target node
     * @param args Number of arguments
     * @return true Success
     * @return false Error
     */
    bool peekStackArguments(Vector<ASTNodePtr>::iterator &it, ASTNode &target, UInt args) noexcept;

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

    void showStack(void) const { _stack.apply([](const auto &elem) { ASTNode::ShowTree(*elem); }); }
};