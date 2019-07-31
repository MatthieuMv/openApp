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

#include <openApp/Core/Expression.hpp>
#include <openApp/Language/Nodes.hpp>

int main(void)
{
    try {
        oA::Item item;

        item.setExpression("x", "y * 2");
        item.setFunction("fct", "height += 2");
        item.addExpressionEvent("x", "++width; fct();");

        // oA::ItemFactory::RegisterBaseItems();
        // auto itm = oA::Lang::Instantiator::ProcessFile("Test.oA");
        // if (!itm)
        //     return 84;
        // itm->show();
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 1;
    }
}