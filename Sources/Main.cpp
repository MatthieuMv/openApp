/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** main
*/

#include "App/Variant.hpp"
#include "Core/Log.hpp"

int main(void)
{
    try {
        oA::Variant var;

        var = oA::String("123");
        ++var;
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
