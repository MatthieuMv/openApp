/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Core/Var.hpp>

int main(void)
{
    oA::Container c = {
        false, 1, 2.5, "3"
    };
    oA::Var v1(c), v2(c);

    if (v1 == v2)
        return 84;
    return 0;
}