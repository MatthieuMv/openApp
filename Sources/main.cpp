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
        int i = 0;
        oA::Signal<> sig;
        auto idx = sig.connect([&i]{ ++i; return true; });

        oA::cout << "Sig idx " << idx << " " << i << oA::endl;
        sig.emit();
        oA::cout << "Sig idx " << idx << " " << i << oA::endl;
        sig.disconnect(idx);
        sig.emit();
        oA::cout << "Sig idx " << idx << " " << i << oA::endl;
        return 0;
    } catch (const std::exception &e) {
        oA::cerr << e.what() << oA::endl;
    }
}
