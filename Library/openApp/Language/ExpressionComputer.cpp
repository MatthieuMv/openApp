/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionComputer
*/

#pragma once

#include <openApp/Core/ExpressionComputer.hpp>

oA::Var oA::ExpressionComputer::Compute(const Tree<ExpressionNode> &tree)
{
    return ExpressionComputer(tree).compute();
}

oA::ExpressionComputer::ExpressionComputer(const Tree<ExpressionNode> &tree)
    : _tree(tree)
{
}

oA::Var oA::ExpressionComputer::compute(void)
{
    return Var();
}