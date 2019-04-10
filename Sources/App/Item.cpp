/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#include "App/Interpreter.hpp"
#include "App/Item.hpp"

void oA::Item::registerItem(void)
{
    oA::Interpreter::GetGlobalNamespace()
        .beginClass<oA::Item>("Item")
            .addProperty("id", oA::Item::id, oA::Item::id);
}