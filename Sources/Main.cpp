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
        auto itm = oA::Parser::ParseFile("Resources/Test.oA", true);
        oA::cout << *itm;
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}