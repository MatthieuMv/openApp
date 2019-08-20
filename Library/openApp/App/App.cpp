/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** App
*/

#include <openApp/App/App.hpp>
#include <openApp/App/ItemFactory.hpp>
#include <openApp/App/Widgets/Window.hpp>
#include <openApp/Language/Instantiator.hpp>

oA::App::App(IRendererPtr &&renderer) : _renderer(std::move(renderer))
{
    ItemFactory::RegisterBaseItems();
}

bool oA::App::onEvent(const Event &event)
{
    if (event.getType() != Event::Window || event.getAs<WindowEvent>().type != WindowEvent::Close)
        return false;
    auto it = _children.find(event.window);
    if (it == _children.end())
        return false;
    _renderer->closeWindow(event.window);
    _children.erase(it);
    return true;
}

bool oA::App::isRunning(void)
{
    if (!_running)
        return false;
    else if (_children.size())
        return true;
    stop();
    return false;
}

void oA::App::run(void)
{
    _running = true;
    onRun();
    while (isRunning()) {
        update();
        render();
    }
}

void oA::App::stop(void)
{
    _running = false;
    onStop();
}

void oA::App::parseString(const String &string, const String &context, bool verbose)
{
    openWindow(oA::Lang::Instantiator::ProcessString(string, context), verbose);
}

void oA::App::parseFile(const String &path, bool verbose)
{
    openWindow(oA::Lang::Instantiator::ProcessFile(path), verbose);
}

void oA::App::openWindow(ItemPtr &&root, bool verbose)
{
    auto *wnd = dynamic_cast<Window *>(root.get());
    auto index = 0;

    if (!_renderer->supportsMultipleWindows() && !_children.empty())
        throw LogicError("App", "Internal renderer doesn't supports multiple windows");
    if (!root.get())
        throw LogicError("App", "Can't add null @Window@");
    if (wnd) {
        index = _renderer->openWindow(wnd->getWindowContext());
        wnd->setWindowIndex(index);
    } else {
        index = _renderer->openWindow(WindowContext(
            "openApp",
            V2i(),
            V2i(root->get("width").toInt(), root->get("height").toInt()),
            Color(),
            WindowContext::Fixed
        ));
    }
    _children[index] = std::move(root);
    if (verbose)
        _children[index]->show();
}

void oA::App::update(void)
{
    pollEvents();
    _children.apply([this](auto &pair) { pair.second->update(*_renderer); });
}

void oA::App::render(void)
{
    _children.apply([this](auto &pair) {
        _renderer->clearWindow(pair.first);
        pair.second->draw(*_renderer);
        _renderer->renderWindow();
    });
}

void oA::App::pollEvents(void)
{
    for (Event event; _renderer->pollEvent(event);) {
        if (onEvent(event))
            continue;
        if (event.window < 0)
            _children.findIf([this, &event](auto &pair) { return pair.second->propagate(*_renderer, event); });
        else {
            _children.findIf([&event, this](auto &pair) {
                if (pair.first != event.window)
                    return false;
                pair.second->propagate(*_renderer, event);
                return true;
            });
        }
    }
}