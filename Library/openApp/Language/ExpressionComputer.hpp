/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionComputer
*/

#pragma once

#include <openApp/Language/Expression.hpp>

namespace oA { class ExpressionComputer; }

class oA::ExpressionComputer
{
public:

    static Var Compute(Tree<ExpressionNode> &tree);

private:
    UMap<String, Var> _locals;

    ExpressionComputer(void) = default;

    Var compute(Tree<ExpressionNode> &node);
    
    Var computeStatement(Tree<ExpressionNode> &node);
    Var computeBlock(Tree<ExpressionNode> &node);
    Var computeDeclaration(Tree<ExpressionNode> &node);
    Var computeCondition(Tree<ExpressionNode> &node);
    Var computeWhile(Tree<ExpressionNode> &node);
    Var computeFor(Tree<ExpressionNode> &node);
    Var computeSwitch(Tree<ExpressionNode> &node);

    Var computeOperator(Tree<ExpressionNode> &node);
    Var assignNode(Tree<ExpressionNode> &node, Var &&res);
};