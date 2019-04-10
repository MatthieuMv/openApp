/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** InterpreterRegister
*/

#include "App/Interpreter.hpp"
#include "App/Item.hpp"

void oA::Interpreter::RegisterInterpreterClasses(void)
{
    static bool init = false;

    if (init)
        return;
    init = true;
    Icout << "Registering Interpreter @base classes@" << oA::endl;
    oA::Item::registerItem();
}