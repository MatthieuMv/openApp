/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** AppFactory
*/

// Retreive every default items in App
#include "App.hpp"

oA::Factory<oA::String, oA::Item> oA::AppFactory::FactoryInstance;

void oA::AppFactory::RegisterBaseItems(void)
{
    Register<Item>();
    Register<Window>();
    Register<Rectangle>();
    Register<Text>();
    Register<EventArea>();
    Register<Button>();
    Register<Image>();
    Register<ImageButton>();
}