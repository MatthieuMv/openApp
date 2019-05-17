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

bool Irrlicht::isRunning(oA::Uint index) const
{
    auto device = context(index).device;

    if (!device->isWindowActive())
        device->yield();
    return device->run();
}

void Irrlicht::clear(oA::Uint index)
{
    if (!context(index).driver->beginScene())
        throw oA::RuntimeError("Irrlicht", "Couldn't begin @driver@ scene");
}

void Irrlicht::draw(oA::Uint index)
{
    if (!context(index).driver->endScene())
        throw oA::RuntimeError("Irrlicht", "Couldn't begin @driver@ scene");
}

bool Irrlicht::pullEvent(oA::Event &evt, oA::Uint index)
{
    auto &events = context(index).events;

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
    return _ctxs.size() - 1;
}

void Irrlicht::pullWindow(oA::WindowContext &ctx, oA::Uint index)
{
    if (index >= _ctxs.size())
        throw oA::LogicError("Irrlicht", "Can't pull invalid index @" + oA::ToString(index) + "@");
    const auto &wnd = context(index);
    const auto &size = wnd.driver->getScreenSize();
    ctx.width = size.Width;
    ctx.height = size.Height;
    if (!ctx.width || !ctx.height)
        throw oA::LogicError("Irrlicht", "Invalid @window@ size");
    ctx.resizable = wnd.resizable;
}

void Irrlicht::drawRectangle(const oA::RectangleContext &ctx, oA::Uint index)
{
    context(index).driver->draw2DRectangle(
        ctx.color.getValue(),
        toRect(ctx)
    );
}

void Irrlicht::drawText(const oA::TextContext &ctx, oA::Uint index)
{
    getFont(ctx.font, index)->draw(
        ctx.text.c_str(),
        toRect(ctx),
        ctx.fontColor.getValue(),
        ctx.hCenter,
        ctx.vCenter
    );
}

void Irrlicht::drawImage(const oA::ImageContext &ctx, oA::Uint index)
{
    auto t = getTexture(ctx.source, index);
    auto rect = toRect(ctx.sourceSize);

    if (!rect.getWidth() && !rect.getHeight()) {
        const auto &s = t->getOriginalSize();
        rect = irr::core::recti({ 0, 0 }, s);
    }
    context(index).driver->draw2DImage(
        t,
        toRect(ctx),
        rect,
        nullptr,
        nullptr,
        true
    );
}

IrrlichtContext &Irrlicht::context(oA::Uint index)
{
    if (index >= _ctxs.size())
        throw oA::AccessError("Irrlicht", "Invalid context index @" + oA::ToString(index) + "@");
    return (_ctxs[index]);
}

const IrrlichtContext &Irrlicht::context(oA::Uint index) const
{
    if (index >= _ctxs.size())
        throw oA::AccessError("Irrlicht", "Invalid context index @" + oA::ToString(index) + "@");
    return (_ctxs[index]);
}

irr::gui::IGUIFont *Irrlicht::getFont(const oA::String &path, oA::Uint index)
{
    if (path.empty())
        return context(index).gui->getBuiltInFont();
    return context(index).gui->getFont(path.c_str());
}

irr::video::ITexture *Irrlicht::getTexture(const oA::String &path, oA::Uint index)
{
    return context(index).driver->getTexture(path.c_str());
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
