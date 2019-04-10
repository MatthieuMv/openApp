/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** main
*/

#include <iostream>
#include <lua.hpp>
#include <LuaBridge.h>
#include "openApp.hpp"

int main(void)
{
    try {
        return 0;
    } catch (const std::exception &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}
