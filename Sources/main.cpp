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
        i.execString("x = 11 + 12");
        oA::cout << "Bool " << i.toBool("x") << oA::endl
                 << "Int " << i.toInt("x") << oA::endl
                 << "Long " << i.toLong("x") << oA::endl
                 << "Float " << i.toFloat("x") << oA::endl
                 << "Double " << i.toDouble("x") << oA::endl
                 << "String " << i.toString("x") << oA::endl;
    } catch (const std::exception &e) {
        oA::cerr << e.what() << oA::endl;
    }
}
