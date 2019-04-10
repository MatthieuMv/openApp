/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#include "Core/Error.hpp"
#include "App/Interpreter.hpp"

lua_State *oA::Interpreter::LuaState = nullptr;
oA::Log oA::Interpreter::Icout(oA::Log::COUT, oA::CSL_LIGHT_BLUE, oA::CSL_LIGHT_GREEN);

luabridge::Namespace oA::Interpreter::GetGlobalNamespace(void)
{
    return luabridge::getGlobalNamespace(LuaState);
}

oA::Interpreter::Interpreter(void)
{
    if (!LuaState) {
        Icout << "Instancing new @lua_State@" << oA::endl;
        LuaState = luaL_newstate();
        if (!LuaState)
            throw oA::RuntimeError("Interpreter", "Couldn't instanciate @lua_State@");
        luaL_openlibs(LuaState);
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