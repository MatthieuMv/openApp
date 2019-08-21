/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** App
*/

#pragma once

#include <openApp/Render/IRenderer.hpp>
#include <openApp/App/Item.hpp>
#include <openApp/App/ItemFactory.hpp>

namespace oA { class App; }

class oA::App
{
public:
    virtual ~App(void) = default;

    App(IRendererPtr &&renderer) : _renderer(std::move(renderer)) { ItemFactory::RegisterBaseItems(); }

    virtual void onRun(void) {}
    virtual void onStop(void) {}
    virtual bool onEvent(const Event &event);

    bool isRunning(void);
    void run(void);
    void stop(void);
    void parseString(const String &string, const String &context = "Root", bool debug = false);
    void parseFile(const String &path, bool debug = false);
    void openWindow(ItemPtr &&root, bool debug = false);

protected:
    UMap<Int, ItemPtr> _children;
    IRendererPtr _renderer;
    bool _running = false;

    void update(void);
    void render(void);
    void pollEvents(void);
};