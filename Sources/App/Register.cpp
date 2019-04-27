/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Register
*/

// std::function
#include <functional>

#include "App/Register.hpp"

void oA::Register::RegisterTypes(oA::Interpreter &interpreter)
{
    static const std::vector<void(*)(Interpreter &)> fcts = {
        &RegisterItem
    };

    for (auto &f : fcts) {
        f(interpreter);
    }
}

#ifdef USE_GLOBAL_INTERPRETER
void oA::Register::RegisterTypesGlobal(void)
{
    RegisterTypes(GlobalInterpreter);
}
#endif

void oA::Register::RegisterItem(oA::Interpreter &interpreter)
{
    interpreter.lua().new_usertype<Item>("Item",
        sol::constructors<Item()>(),
        "x", sol::property(&Item::x, &Item::set_x),
        "y", sol::property(&Item::y, &Item::set_y),
        "width", sol::property(&Item::width, &Item::set_width),
        "height", sol::property(&Item::height, &Item::set_height)
    );
}