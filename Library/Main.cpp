/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Core/Log.hpp>
#include <openApp/SDLApp.hpp>

int main(void)
{
    try {
        X x<oA::SDLRenderer>();
    } catch (oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
    }
    return 0;
}
