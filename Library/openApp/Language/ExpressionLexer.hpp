/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExprLexer
*/

#pragma once

#include <openApp/Types/Variant.hpp>
#include <openApp/Language/Lexer.hpp>
#include <openApp/Language/ExpressionNode.hpp>
#include <openApp/Core/Expression.hpp>

namespace oA { class ExpressionLexer; }

class oA::ExpressionLexer : public Lexer<ExpressionNode>
{
public:
    enum TokenType {
        Root = 0,
        Operator,
        Statement,
        Expr,
        Value,
        Declaration
    };

    using Lexer<ExpressionNode>::LexTree;

    /**
     * @brief Process a string, storing the result in target LexTree
     *
     * @param toProcess String to process
     * @param target Target
     */
    static void ProcessString(String &&toProcess, LexTree &target);

private:
    using Lexer::Lexer;

    virtual ~ExpressionLexer(void) = default;

    virtual bool process(const String &end = String());
};