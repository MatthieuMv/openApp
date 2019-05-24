/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** main
*/

#include "openApp.hpp"

int main(void)
{
    try {
        oA::Item item;
        item.makeExpression("x", "width > 100 ? 1 : (width <= 50 ? 2 : (width >= 75 ? 3 : 4))");
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}