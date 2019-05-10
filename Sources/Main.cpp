/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** main
*/

#include "openApp.hpp"

int main(void)
{
    try {
        //auto itm = oA::Parser::ParseFile("Resources/Test.oA", true);
        //oA::cout << *itm;
        oA::String expr = "1+2*3 >2 ?3 :";

        oA::FormatExpression(expr);
        oA::cout << "Expr: " << expr << oA::endl;
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}