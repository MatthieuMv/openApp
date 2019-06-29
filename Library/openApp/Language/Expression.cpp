/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Language/ExpressionComputer.hpp>

void oA::Expression::call(void)
{
    if (!compute())
        this->emit();
}

oA::Uint oA::Expression::connectEvent(Expression &&expr) noexcept
{
    return this->connect([event = std::move(expr)](void) mutable {
        event.call();
        return true;
    });
}

bool oA::Expression::compute(void)
{
    if (_tree.children.empty())
        return false;
    return set(ExpressionComputer::Compute(_tree));
}

void oA::Expression::setExpressionTree(Tree<ExpressionNode> &&tree)
{
    _tree = std::move(tree);
}