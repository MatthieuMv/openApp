/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** main
*/

#include <iostream>
#include "openApp.hpp"

int main(void)
{
    try {
        oA::Interpreter i;
        i.execString("x = 11.123 + 12.987");
        oA::cout << "Bool " << i.getBool("x") << oA::endl
                 << "Int " << i.getInt("x") << oA::endl
                 << "Long " << i.getLong("x") << oA::endl
                 << "Float " << i.getFloat("x") << oA::endl
                 << "Double " << i.getDouble("x") << oA::endl
                 << "String " << i.getString("x") << oA::endl;
    } catch (const std::exception &e) {
        oA::cerr << e.what() << oA::endl;
    }
}
