/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Core/Log.hpp>
#include <openApp/SDLApp.hpp>
#include <openApp/Language/ShuntingYard.hpp>

int main(void)
{
    try {
        oA::Item root;
        root.setID("root");
        root.appendChild(std::make_shared<oA::Item>()).setID("target");
        auto &container = root.appendChild(std::make_shared<oA::Item>());
        container.setID("container");
        auto &source = container.appendChild(std::make_shared<oA::Item>());
        source.setID("source");
        auto res = source.findExpr("root.x");
        oA::cout << "Res = " << res.get() << oA::endl;
        return 0;
    } catch (oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
