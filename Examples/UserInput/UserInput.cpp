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

        app.parseFile("UserInput.oA"); // Parse class 'UserInput'
        app.run(); // Run the UserInput App
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}