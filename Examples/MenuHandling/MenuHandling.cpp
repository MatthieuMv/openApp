/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MenuHandling
*/

#include "openApp.hpp"
#include "IrrlichtApp.hpp"

int main(void)
{
    try {
        oA::IrrlichtApp app(true);

        app.parseFile("MenuHandling.oA");
        app.run();
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}