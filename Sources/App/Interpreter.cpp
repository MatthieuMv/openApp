/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#include "App/Interpreter.hpp"

lua_State *oA::Interpreter::LuaState = nullptr;
oA::Log oA::Interpreter::Icout(oA::Log::COUT, oA::CSL_LIGHT_BLUE, oA::CSL_LIGHT_CYAN);

luabridge::Namespace oA::Interpreter::GetGlobalNamespace(void)
{
    return luabridge::getGlobalNamespace(LuaState);
}

oA::Interpreter::Interpreter(void)
{
    if (!LuaState) {
        Icout << "Instancing new @lua_State@" << oA::endl;
        LuaState = luaL_newstate();
    }
    oA::Interpreter::RegisterInterpreterClasses();
}

oA::Interpreter::~Interpreter(void)
{
    if (LuaState) {
        Icout << "Closing @lua_State@ instance" << oA::endl;
        lua_close(LuaState);
    }
}