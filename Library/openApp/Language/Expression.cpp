/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Language/Expression.hpp>

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
    return false;
}
