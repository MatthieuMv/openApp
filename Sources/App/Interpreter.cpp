/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#include "Core/Error.hpp"
#include "App/Interpreter.hpp"
#include "App/Register.hpp"

oA::Interpreter::Interpreter()
{
    _lua.open_libraries(sol::lib::base);
    oA::Register::RegisterTypes(*this);
}

oA::Interpreter::~Interpreter()
{
}
