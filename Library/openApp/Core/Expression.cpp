/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Core/Expression.hpp>

oA::Expression &oA::Expression::operator=(Expression &&other)
{
    swap(other);
    return *this;
}

bool oA::Expression::compute(void)
{
    if (!_tree)
        return false;
    return set(_tree->compute());
}

void oA::Expression::call(void)
{
    if (!compute())
        this->emit();
}

oA::Uint oA::Expression::connectEvent(ExpressionPtr &&expr)
{
    if (!expr)
        throw LogicError("Expression", "Can't add @null@ event");
    return this->connect([event = std::move(expr)](void) mutable {
        event->call();
        return true;
    });
}

void oA::Expression::show(Int tab) const noexcept
{
    if (_tree)
        Lang::ASTNode::ShowTree(*_tree, tab);
}