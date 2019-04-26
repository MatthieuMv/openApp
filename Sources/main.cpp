/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** main
*/

#include <iostream>
#include "openApp.hpp"

int main(void)
{
    try {
        oA::Interpreter i;

        i.lua();
        return 0;
    } catch (const std::exception &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
