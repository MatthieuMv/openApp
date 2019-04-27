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
        oA::Register::RegisterTypesGlobal();
        oA::GlobalInterpreter.lua().script("itm = Item.new(); itm.x = 2");
        oA::Item &ref = oA::GlobalInterpreter.lua()["itm"];
        oA::cout << "Item x = " << ref.x() << oA::endl;
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
