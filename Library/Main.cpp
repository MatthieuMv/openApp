/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Core/Log.hpp>
#include <openApp/Language/Nodes.hpp>

// #include <openApp/Core/Property.hpp>
// #include <openApp/Core/Log.hpp>

// int main(void)
// {
//     oA::Property var(42);

//     var.connect([&var]{ oA::cout << "#Var#: @" << var.toString() << "@" << oA::endl; return true; });
//     var = 0;
//     var += 1;
//     ++var;
//     var++;
//     --var;
//     var--;
//     var -= 1;
//     var *= 0.5;
//     var %= 1;
// }


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
