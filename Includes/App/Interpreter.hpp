/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#pragma once

#include <lua.hpp>
#include <LuaBridge.h>
#include "Core/Log.hpp"
#include "Core/Mutex.hpp"
#include "Core/Memory.hpp"

namespace oA { class Interpreter; }

/*
    Interpreter class will make the link between openApp, lua C API and LuaBridge.
    An instance of interpreter will only configure the static class members and handle lua stack's lifetime.
    User can register custom classes with the help of LuaBridge and 'GetGlobalNamespace' function
*/
class oA::Interpreter
{
    /* Static Class Interpreter */
public:
    static luabridge::Namespace GetGlobalNamespace(void);
    static void RegisterInterpreterClasses(void);

    static lua_State *LuaState;
    static Log Icout;

    /* Instanciable Class Interpreter */
public:
    Interpreter(void);
    ~Interpreter(void);
};