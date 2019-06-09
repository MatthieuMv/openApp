/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/App/Item.hpp>
#include <iostream>

int main(void)
{
    oA::Item item;

    std::cout << "ID = " << item.get("id")->index() << std::endl;
    item.get("id").set("item");
    std::cout << "SET " << item.get("id")->toString() << std::endl;
    std::cout << "ID = " << item.get("id")->index() << std::endl;
    item.append("myVar") = 42;
}