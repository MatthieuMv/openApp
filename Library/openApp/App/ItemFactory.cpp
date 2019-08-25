/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemFactory
*/

#include <openApp/App/ItemFactory.hpp>
#include <openApp/App/Items/Window.hpp>
#include <openApp/App/Items/Button.hpp>
#include <openApp/App/Items/ImageButton.hpp>
#include <openApp/App/Items/TilesetButton.hpp>
#include <openApp/App/Items/IndexView.hpp>
#include <openApp/App/Items/Timer.hpp>

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
    Register<Label>();
    Register<Image>();
    Register<Tileset>();
    Register<EventArea>();
    Register<Button>();
    Register<ImageButton>();
    Register<TilesetButton>();
    Register<IndexView>();
    Register<Timer>();
}