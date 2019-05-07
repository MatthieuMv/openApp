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
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
