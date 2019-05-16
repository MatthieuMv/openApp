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
        oA::String path = "Resources/Ultimate.oA";
        auto itm = oA::Parser::ParseFile(path, true);
        if (!itm)
            return 84;
        oA::cout << oA::endl << "#" + path + "#" << ":" << oA::endl << *itm;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}