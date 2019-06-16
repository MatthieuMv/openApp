/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IrrlichtContext
*/

#pragma once

// Irrlicht library
#include <irrlicht.h>

// UMap
#include "Core/UMap.hpp"
// Queue
#include "Core/Queue.hpp"
// String
#include "Core/String.hpp"
// WindowContext
#include "App/Context.hpp"
// Event
#include "App/Event.hpp"

struct IrrlichtContext
{
    IrrlichtContext(const oA::WindowContext &ctx)
    {
        device = irr::createDevice(
            irr::video::EDT_OPENGL,
            irr::core::dimension2du(ctx.size.x, ctx.size.y)
        );
        if (!device)
            throw oA::RuntimeError("Irrlicht", "Couldn't open @device@");
        resizable = ctx.resizable;
        device->setResizable(resizable);
        driver = device->getVideoDriver();
        manager = device->getSceneManager();
        gui = device->getGUIEnvironment();
    }

    irr::IrrlichtDevice *device = nullptr;
    irr::video::IVideoDriver *driver = nullptr;
    irr::scene::ISceneManager *manager = nullptr;
    irr::gui::IGUIEnvironment *gui = nullptr;
    oA::UMap<oA::String, irr::gui::IGUIFont *> fonts;
    oA::UMap<oA::String, irr::video::ITexture *> textures;
    bool resizable = false;
    oA::Queue<oA::Event> events;
    oA::UMap<oA::Uint, irr::scene::ISceneNode *> nodes;
    oA::Uint maxNodeIdx = 0;
};