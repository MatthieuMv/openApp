/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/App/App.hpp>
#include <openApp/Core/Log.hpp>
#include <openApp/Renderer/SDL/SDLRenderer.hpp>

int main(void)
{
    try {
        oA::App app(std::make_unique<oA::SDLRenderer>());

        app.parseFile("Main.oA", true);
        app.run();
    } catch (oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
    }
    return 0;
}
