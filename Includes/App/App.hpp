/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** App
*/

#pragma once

// List
#include "Core/List.hpp"
// Item
#include "App/Item.hpp"
// IApp
#include "App/IApp.hpp"
// Parser
#include "App/Parser.hpp"
// Window
#include "App/Window.hpp"

namespace oA { template<typename Renderer> class App; }

template<typename Renderer>
class oA::App
{
public:
    App(bool verbose = false) : _verbose(verbose) {
        _renderer = MakeShared<Renderer>();
        if (!_renderer)
            throw RuntimeError("App", "Couldn't instanciate @renderer@");
    }

    virtual ~App(void) {}

    /* User only has acces to running state and stop function */
    bool isRunning(void) const noexcept { return _running; }
    void stop(void) noexcept { setRunning(false); }

    /* Run the app, receiving events and drawing its elements until every windows are closed */
    virtual void run(void) {
        setRunning(true);
        onRun();
        while (isRunning()) {
            update();
            render();
        }
        onStop();
    }

    /* App event virtual functions */
    virtual void onRun(void) {}
    virtual void onStop(void) {}

    /* Each parseFile call will add a new root item, creating a new window */
    void parseFile(const String &path) {
        WindowContext ctx;
        ItemPtr ptr = Parser::ParseFile(path, _verbose);
        Window *wnd = dynamic_cast<Window *>(ptr.get());
        if (_verbose) {
            cout << "#" + path + "#" << ": " << endl << *ptr;
        }
        if (!wnd)
            ptr->getItemContext(ctx);
        else
            wnd->getWindowContext(ctx);
        _renderer->pushWindow(ctx);
        _roots.push_back(ptr);
    }

protected:
    IRendererPtr _renderer;
    List<ItemPtr> _roots;
    bool _running = false;
    bool _verbose = false;

    void setRunning(bool value) noexcept { _running = value; }

    void update(void) {
        auto i = 0;
        oA::Event evt;
        for (auto &root : _roots) {
            _renderer->setTargetContext(i);
            while (_renderer->pullEvent(evt)) {
                root->propagate(evt);
            }
            ++i;
        }
    }

    void render(void) {
        auto i = 0;
        auto appActive = false;
        for (auto root : _roots) {
            if (!_renderer->setTargetContext(i) || !_renderer->isRunning())
                continue;
            appActive = true;
            _renderer->clear();
            root->render(*_renderer);
            _renderer->draw();
            ++i;
        }
        if (!appActive)
            setRunning(false);
    }
};