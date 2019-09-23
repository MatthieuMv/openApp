/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemFactory
*/

#include <openApp/App/ItemFactory.hpp>
#include <openApp/Items/Window.hpp>
#include <openApp/Items/Circle.hpp>
#include <openApp/Items/Button.hpp>
#include <openApp/Items/ImageButton.hpp>
#include <openApp/Items/TilesetButton.hpp>
#include <openApp/Items/AnimatedTileButton.hpp>
#include <openApp/Items/IndexView.hpp>
#include <openApp/Items/Timer.hpp>
#include <openApp/Items/Column.hpp>
#include <openApp/Items/Row.hpp>
#include <openApp/Items/DragArea.hpp>
#include <openApp/Items/TextInput.hpp>
#include <openApp/Items/ScrollColumn.hpp>
#include <openApp/Items/ScrollRow.hpp>

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
    Register<Circle>();
    Register<Label>();
    Register<Image>();
    Register<Tileset>();
    Register<EventArea>();
    Register<Button>();
    Register<ImageButton>();
    Register<AnimatedTile>();
    Register<TilesetButton>();
    Register<AnimatedTileButton>();
    Register<IndexView>();
    Register<Timer>();
    Register<Layout>();
    Register<Column>();
    Register<Row>();
    Register<DragArea>();
    Register<TextInput>();
    Register<ScrollLayout>();
    Register<ScrollColumn>();
    Register<ScrollRow>();
}