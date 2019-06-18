/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/App/Item.hpp>

int main(void)
{
    oA::Item root;
    auto &child = root.appendChild(std::make_shared<oA::Item>());
    auto &child2 = root.appendChild(std::make_shared<oA::Item>());
    auto &sub = child.appendChild(std::make_shared<oA::Item>());
    auto &sub2 = child2.appendChild(std::make_shared<oA::Item>());

    root.setID("root");
    child.setID("child");
    child2.setID("child2");
    sub.setID("sub");
    sub2.setID("sub2");
}