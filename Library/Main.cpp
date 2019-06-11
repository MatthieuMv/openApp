/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Core/Var.hpp>
#include <iostream>

int main(void)
{
    oA::Var v1(42), v2(43);

    for (unsigned long long i = 0; i < 1000000; ++i) {
        v1 + v2;
    }
    v1 = oA::Var("43");
    v2 = oA::Var("32");
    for (unsigned long  i = 0; i < 1000000; ++i) {
        v1 + v2;
    }
}