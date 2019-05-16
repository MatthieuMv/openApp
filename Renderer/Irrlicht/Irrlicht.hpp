/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Irrlicht
*/

#pragma once

// irrlicht
#include <irrlicht/irrlicht.h>
// IRenderer
#include "App/IRenderer.hpp"
// Vector
#include "Core/Vector.hpp"
// UMap
#include "Core/UMap.hpp"

class Irrlicht : public oA::IRenderer
{
public:
    struct Context
    {
        Context(const oA::WindowContext &ctx);

        irr::IrrlichtDevice *device = nullptr;
        irr::video::IVideoDriver *driver = nullptr;
        irr::scene::ISceneManager *manager = nullptr;
        irr::gui::IGUIEnvironment *gui = nullptr;
        oA::UMap<oA::String, irr::gui::IGUIFont *> fonts;
        oA::UMap<oA::String, irr::video::ITexture *> textures;
        bool resizable = false;
    };

    Irrlicht(void) = default;
    virtual ~Irrlicht(void);

    /* Virtual functions */
    virtual bool isRunning(oA::Uint idx = 0) const;
    virtual void clear(oA::Uint idx = 0);
    virtual void draw(oA::Uint idx = 0);
    virtual bool pullEvent(oA::Event &evt, oA::Uint index = 0);
    oA::Uint pushWindow(const oA::WindowContext &ctx);
    virtual void pullWindow(oA::WindowContext &ctx, oA::Uint idx = 0);
    virtual void drawRectangle(const oA::RectangleContext &ctx, oA::Uint idx = 0);
    virtual void drawText(const oA::TextContext &ctx, oA::Uint idx = 0);
    virtual void drawImage(const oA::ImageContext &ctx, oA::Uint idx = 0);

private:
    oA::Vector<Context> _ctxs;

    Context &context(oA::Uint index);
    const Context &context(oA::Uint index) const;
    irr::gui::IGUIFont *getFont(const oA::String &path, oA::Uint index);
    irr::video::ITexture *getTexture(const oA::String &path, oA::Uint index);
    irr::core::recti toRect(const oA::ItemContext &ctx) const noexcept;
};
