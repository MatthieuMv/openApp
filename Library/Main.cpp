/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Language/ShuntingYard.hpp>

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

int main(void)
{
    oA::Item item;

    oA::Lang::ShuntingYard::ProcessString(item, "x", "(((y >= 2 ? 42 : 24) * 2) / 4) * 2", oA::Lang::ShuntingYard::Expression);
    item.getPtr("x")->show();
    item.get("y") = 1;
    cr_assert_eq(item.getAs<oA::Number>("x"), 24);
    item.get("y") = 2;
    cr_assert_eq(item.getAs<oA::Number>("x"), 42);
}