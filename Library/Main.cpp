/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Types/Error.hpp>
#include <openApp/Core/Log.hpp>
#include <openApp/App/ItemFactory.hpp>
#include <openApp/Language/Instantiator.hpp>

int main(void)
{
    try {
        oA::ItemFactory::RegisterBaseItems();
        auto itm = oA::Lang::Instantiator::ProcessFile("Test.oA");
        if (!itm)
            return 84;
        itm->show();
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 1;
    }
}