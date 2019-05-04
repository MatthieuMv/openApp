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
        oA::Interpreter core;
        core.lua().script("itm = Item.new(); itm.x = 2");
        oA::Item &ref = core.lua()["itm"];
        oA::cout << "Item x = " << ref.x() << oA::endl;
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
