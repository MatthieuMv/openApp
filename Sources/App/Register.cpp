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

void oA::Register::RegisterItem(oA::Interpreter &interpreter)
{
    interpreter.lua().new_usertype<Item>("Item",
        sol::constructors<Item()>(),
        "x", sol::property(&Item::get_x, &Item::set_x),
        "y", sol::property(&Item::get_y, &Item::set_y),
        "width", sol::property(&Item::get_width, &Item::set_width),
        "height", sol::property(&Item::get_height, &Item::set_height)
    );
}