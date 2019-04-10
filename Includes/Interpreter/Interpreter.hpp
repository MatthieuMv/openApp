/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Interpreter
*/

#pragma once

#include "Core/Scalar.hpp"
#include "Core/String.hpp"
#include "Core/Variant.hpp"
#include "Core/Memory.hpp"

struct lua_State;

namespace oA { class Interpreter; }

class oA::Interpreter
{
public:
    Interpreter(void);
    ~Interpreter(void);

    /* Execute lua code */
    Bool execString(const String &string);
    Bool execFile(const String &path);

    /* Typed variable getters */
    Bool getBool(const String &varname);
    Int getInt(const String &varname);
    Long getLong(const String &varname);
    Float getFloat(const String &varname);
    Double getDouble(const String &varname);
    String getString(const String &varname);

    /* Template variable getter */
    //template<typename T>
    //T get(const String &varname);

private:
    oA::Shared<lua_State> _state;
};