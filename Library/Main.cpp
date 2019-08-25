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
        oA::Item item;

        oA::Lang::ShuntingYard::ProcessString(item, "x",
    "switch (x) {\n\
    case 1:\n\
        print(\"case x = 1\")\n\
        y = 4;\n\
        break;\n\
    case 2:\n\
        print(\"case x = 2\")\n\
        y = 42;\n\
        break;\n\
    case 3:\n\
        print(\"case x = 3\")\n\
        y = 420;\n\
        break;\n\
    default:\n\
        print(\"default\")\n\
        y = 10;\n\
        break;\n\
    }", oA::Lang::ShuntingYard::Event);

        item.addExpressionEvent("y", "print(\"y = \", y)");
        oA::cout << "x = " << item.get("x").toUint() << oA::endl;
        item.get("x") = 2;
        oA::cout << "x = " << item.get("x").toUint() << oA::endl;
    return 0;
    } catch (oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
