/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Register
*/

#pragma once

#include "App.hpp"

namespace oA::Register
{
    /* Global registeration */
    void RegisterTypes(Interpreter &interpreter);

    #ifdef USE_GLOBAL_INTERPRETER
    void RegisterTypesGlobal(void);
    #endif

    void RegisterItem(Interpreter &interpreter);
}