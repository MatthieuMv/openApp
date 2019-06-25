/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionComputer
*/

#pragma once

#include <openApp/Core/Expression.hpp>

namespace oA { class ExpressionComputer; }

class oA::ExpressionComputer
{
public:

    static Var Compute(const Tree<ExpressionNode> &tree);

private:
    const Tree<ExpressionNode> &_tree;
    UMap<String, Var> _locals;

    ExpressionComputer(const Tree<ExpressionNode> &tree);

    Var compute(void);
};