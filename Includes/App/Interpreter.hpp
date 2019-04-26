/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#pragma once

#include "sol.hpp"
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
public:
    Interpreter(void);
    ~Interpreter(void);

    sol::lua &lua(void) noexcept { return (_lua); }
    const sol::lua &lua(void) const noexcept { return (_lua); }

private:
    sol::state _lua;
};