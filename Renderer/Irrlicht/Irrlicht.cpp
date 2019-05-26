/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Irrlicht
*/

// RuntimeError
#include "Core/Error.hpp"
// Irrlicht
#include "Irrlicht.hpp"

Irrlicht::~Irrlicht(void)
{
    for (auto &c : _ctxs) {
        c.device->drop();
    }
}

bool Irrlicht::setTargetContext(oA::Uint idx)
{
    if (idx >= _ctxs.size())
        return false;
    _idx = idx;
    return true;
}

bool Irrlicht::isRunning(void) const
{
    auto device = context().device;

    if (!device->isWindowActive())
        device->yield();
    return device->run();
}

void Irrlicht::clear(void)
{
    if (!context().driver->beginScene())
        throw oA::RuntimeError("Irrlicht", "Couldn't begin @driver@ scene");
}

void Irrlicht::draw(void)
{
    if (!context().driver->endScene())
        throw oA::RuntimeError("Irrlicht", "Couldn't begin @driver@ scene");
}

void Irrlicht::drawScene(void)
{
    context().manager->drawAll();
}

bool Irrlicht::pullEvent(oA::Event &evt)
{
    auto &events = context().events;

    if (events.empty())
        return false;
    evt = events.front();
    events.pop();
    return true;
}

oA::Uint Irrlicht::pushWindow(const oA::WindowContext &ctx)
{
    _ctxs.emplace_back(ctx);
    _handler = oA::MakeUnique<EventHandler>(_ctxs.back());
    _ctxs.back().device->setEventReceiver(_handler.get());
    irr::core::stringw str;
    str.append(ctx.title.c_str());
    _ctxs.back().device->setWindowCaption(str.c_str());
    return _ctxs.size() - 1;
}

void Irrlicht::pullWindow(oA::WindowContext &ctx)
{
    const auto &wnd = context();
    const auto &size = wnd.driver->getScreenSize();

    ctx.width = size.Width;
    ctx.height = size.Height;
    if (!ctx.width || !ctx.height)
        throw oA::LogicError("Irrlicht", "Invalid @window@ size");
    ctx.resizable = wnd.resizable;
}

void Irrlicht::drawRectangle(const oA::RectangleContext &ctx)
{
    context().driver->draw2DRectangle(
        ctx.color.getValue(),
        toRect(ctx)
    );
}

void Irrlicht::drawText(const oA::TextContext &ctx)
{
    getFont(ctx.font)->draw(
        ctx.text.c_str(),
        toRect(ctx),
        ctx.fontColor.getValue(),
        ctx.hCenter,
        ctx.vCenter
    );
}

void Irrlicht::drawImage(const oA::ImageContext &ctx)
{
    auto t = getTexture(ctx.source);
    auto rect = toRect(ctx.sourceSize);

    if (!rect.getWidth() && !rect.getHeight()) {
        const auto &s = t->getOriginalSize();
        rect = irr::core::recti({ 0, 0 }, s);
    }
    context().driver->draw2DImage(
        t,
        toRect(ctx),
        rect,
        nullptr,
        nullptr,
        true
    );
}

void Irrlicht::drawCircle(const oA::CircleContext &ctx)
{
    auto radius = ctx.radius;
    auto side = ((ctx.radius * 2) / std::sqrt(2)) / 2;
    auto driver = context().driver;

    if (ctx.filled)
        driver->draw2DRectangle(
            ctx.color.getValue(),
            irr::core::recti(ctx.x - side, ctx.y - side, ctx.x + side, ctx.y + side)
        );
    do {
        driver->draw2DPolygon(
            irr::core::vector2di(ctx.x, ctx.y),
            radius,
            ctx.color.getValue(),
            10
        );
        radius -= 0.2;
    } while (ctx.filled && radius > side);
}

IrrlichtContext &Irrlicht::context(void)
{
    if (_idx >= _ctxs.size())
        throw oA::AccessError("Irrlicht", "Invalid context index @" + oA::ToString(_idx) + "@");
    return (_ctxs[_idx]);
}

const IrrlichtContext &Irrlicht::context(void) const
{
    if (_idx >= _ctxs.size())
        throw oA::AccessError("Irrlicht", "Invalid context index @" + oA::ToString(_idx) + "@");
    return (_ctxs[_idx]);
}

irr::gui::IGUIFont *Irrlicht::getFont(const oA::String &path)
{
    if (path.empty())
        return context().gui->getBuiltInFont();
    return context().gui->getFont(path.c_str());
}

irr::video::ITexture *Irrlicht::getTexture(const oA::String &path)
{
    return context().driver->getTexture(path.c_str());
}

irr::core::recti Irrlicht::toRect(const oA::ItemContext &ctx) const noexcept
{
    return irr::core::recti(
        static_cast<irr::s32>(ctx.x),
        static_cast<irr::s32>(ctx.y),
        static_cast<irr::s32>(ctx.x + ctx.width),
        static_cast<irr::s32>(ctx.y + ctx.height)
    );
}

bool Irrlicht::supportsMultiContexts(void) const noexcept
{
    return false;
}

bool Irrlicht::supports3D(void) const noexcept
{
    return true;
}