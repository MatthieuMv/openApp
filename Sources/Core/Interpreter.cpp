/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#include "lua.hpp"
#include "Core/Error.hpp"
#include "Core/Interpreter.hpp"

oA::Interpreter::Interpreter(void)
{
    _state = luaL_newstate();
}

oA::Interpreter::~Interpreter(void)
{
    lua_close(_state);
}

oA::Bool oA::Interpreter::execString(const oA::String &string)
{
    return !luaL_dostring(_state, string.c_str());
}

oA::Bool oA::Interpreter::execFile(const oA::String &path)
{
    return !luaL_dofile(_state, path.c_str());
}

oA::Bool oA::Interpreter::getBool(const oA::String &varname)
{
    lua_getglobal(_state, varname.c_str());
    return lua_toboolean(_state, 1);
}

oA::Int oA::Interpreter::getInt(const oA::String &varname)
{
    return static_cast<oA::Int>(getLong(varname));
}

oA::Long oA::Interpreter::getLong(const oA::String &varname)
{
    int success = 0;

    lua_getglobal(_state, varname.c_str());
    lua_tointegerx(_state, 1, &success);
    if (!success)
        throw oA::TypeError("Interpreter", "Variable @" + varname + "@ is not an integer");
}

oA::Float oA::Interpreter::getFloat(const oA::String &varname)
{
    return static_cast<oA::Float>(getDouble(varname));
}

oA::Double oA::Interpreter::getDouble(const oA::String &varname)
{
    int success = 0;

    lua_getglobal(_state, varname.c_str());
    lua_tonumberx(_state, 1, &success);
    if (!success)
        throw oA::TypeError("Interpreter", "Variable @" + varname + "@ is not a floating point");
}

oA::String oA::Interpreter::getString(const oA::String &varname)
{
    const char *res;

    lua_getglobal(_state, varname.c_str());
    res = lua_tostring(_state, 1);
    if (!res)
        throw oA::TypeError("Interpreter", "Variable @" + varname + "@ is not a string");
    return res;
}

template<typename T>
T oA::Interpreter::get(const String &varname)
{

}