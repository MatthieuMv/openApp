/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#include "lua.hpp"
#include "Core/Error.hpp"
#include "Interpreter/Interpreter.hpp"

oA::Interpreter::Interpreter(void) : _state(luaL_newstate(), lua_close)
{

}

oA::Interpreter::~Interpreter(void)
{
}

oA::Bool oA::Interpreter::execString(const oA::String &string)
{
    return !luaL_dostring(_state.get(), string.c_str());
}

oA::Bool oA::Interpreter::execFile(const oA::String &path)
{
    return !luaL_dofile(_state.get(), path.c_str());
}

oA::Bool oA::Interpreter::getBool(const oA::String &varname)
{
    lua_getglobal(_state.get(), varname.c_str());
    return lua_toboolean(_state.get(), 1);
}

oA::Int oA::Interpreter::getInt(const oA::String &varname)
{
    return static_cast<oA::Int>(getLong(varname));
}

oA::Long oA::Interpreter::getLong(const oA::String &varname)
{
    int success = 0;
    oA::Long res;

    lua_getglobal(_state.get(), varname.c_str());
    res = lua_tointegerx(_state.get(), 1, &success);
    if (!success)
        throw oA::TypeError("Interpreter", "Variable @" + varname + "@ is not an integer");
    return res;
}

oA::Float oA::Interpreter::getFloat(const oA::String &varname)
{
    return static_cast<oA::Float>(getDouble(varname));
}

oA::Double oA::Interpreter::getDouble(const oA::String &varname)
{
    int success = 0;
    oA::Double res;

    lua_getglobal(_state.get(), varname.c_str());
    res = lua_tonumberx(_state.get(), 1, &success);
    if (!success)
        throw oA::TypeError("Interpreter", "Variable @" + varname + "@ is not a floating point");
    return res;
}

oA::String oA::Interpreter::getString(const oA::String &varname)
{
    const char *res;

    lua_getglobal(_state.get(), varname.c_str());
    res = lua_tostring(_state.get(), 1);
    if (!res)
        throw oA::TypeError("Interpreter", "Variable @" + varname + "@ is not a string");
    return res;
}