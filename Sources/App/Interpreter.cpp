/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#include "Core/Error.hpp"
#include "App/Interpreter.hpp"

Interpreter::Interpreter()
{
    _lua.open_libraries(sol::lib::base);
}

Interpreter::~Interpreter()
{
}
