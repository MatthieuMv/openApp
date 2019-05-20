/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IrrlichtMain
*/

#include "IrrlichtApp.hpp"

int main(void)
{
    try {
        oA::IrrlichtApp app(true); // Enable verbose to show parsing log

        app.parseFile("HelloWorld.oA"); // Parse class 'HelloWord'
        app.run(); // Run the HelloWorld App
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}