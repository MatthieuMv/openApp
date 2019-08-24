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
        oA::SDLApp app;

        app.parseFile("Library/Tests/TestMedias/Test02.oA");
        app.run();
        return 0;
    } catch (oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
