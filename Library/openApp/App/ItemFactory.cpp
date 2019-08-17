/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemFactory
*/

#include <openApp/App/ItemFactory.hpp>
#include <openApp/App/Widgets/Window.hpp>
#include <openApp/App/Widgets/Rectangle.hpp>
#include <openApp/App/Widgets/EventArea.hpp>

oA::UMap<oA::String, oA::Function<oA::ItemPtr(void)>> oA::ItemFactory::Components;

bool oA::ItemFactory::Exists(const String &name)
{
    return Components.find(name) != Components.end();
}

oA::ItemPtr oA::ItemFactory::Instanciate(const String &name)
{
    auto it = Components.find(name);

    return it != Components.end() ? it->second() : nullptr;
}

void oA::ItemFactory::RegisterBaseItems(void)
{
    if (Exists("Item"))
        return;
    Register<Item>();
    Register<Window>();
    Register<Rectangle>();
    Register<EventArea>();
}