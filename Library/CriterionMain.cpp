/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Core/Log.hpp>
#include <openApp/Language/Nodes.hpp>

void cr_assert(bool res)
{
    if (!res)
        throw;
}

template<typename T, typename U>
void cr_assert_eq(const T &x, const U &y)
{
    if (x != y)
        throw;
}

void foo(void)
{
    throw oA::LogicError("Error");
}

void call(void)
{
}

int main(void)
{
}