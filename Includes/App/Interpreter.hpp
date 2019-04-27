/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#pragma once

#define USE_GLOBAL_INTERPRETER

#include "sol.hpp"
#include "Core/Log.hpp"
#include "Core/Mutex.hpp"
#include "Core/Memory.hpp"

namespace sol { class state; }
namespace oA { class Interpreter; }

/*
    Interpreter class will make the link between openApp, lua C API and sol2.
    An instance of interpreter will only configure the static class members and handle sol2's lua stack's lifetime.
*/
class oA::Interpreter
{
public:
    Interpreter(void);
    ~Interpreter(void);

    sol::state &lua(void) noexcept { return (_lua); }
    const sol::state &lua(void) const noexcept { return (_lua); }

private:
    sol::state _lua;
};

#ifdef USE_GLOBAL_INTERPRETER
namespace oA { extern Interpreter GlobalInterpreter; }
#endif