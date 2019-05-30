/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Irrlicht
*/

#pragma once

// IRenderer
#include "App/IRenderer3D.hpp"
// Vector
#include "Core/Vector.hpp"

// EventHandler
#include "EventHandler.hpp"

/* Irrlicht is an IRenderer3D's implementation :
    It can be used from 2D gui to 3D games for Linux, Windows and OSX
    ! Not compatible with multiple windows, use App::parseFile 1 time !
    ! Irrlicht doesn't suppport dynamic text size so load a single file per size !
*/
class Irrlicht : public oA::IRenderer3D
{
public:
    Irrlicht(void) {}
    virtual ~Irrlicht(void);

    /* Virtual 2D functions */
    virtual bool setTargetContext(oA::Uint idx);
    virtual bool isRunning(void) const;
    virtual void clear(void);
    virtual void draw(void);
    virtual bool pullEvent(oA::Event &evt);
    virtual oA::Uint pushWindow(const oA::WindowContext &ctx);
    virtual void pullWindow(oA::WindowContext &ctx);
    virtual void drawRectangle(const oA::RectangleContext &ctx);
    virtual void drawText(const oA::TextContext &ctx);
    virtual void drawImage(const oA::ImageContext &ctx);
    virtual void drawCircle(const oA::CircleContext &ctx);
    virtual bool supports3D(void) const noexcept;
    virtual bool supportsMultiContexts(void) const noexcept;

    /* Virtual 3D functions */
    virtual void clearScene(void);
    virtual void drawScene(void);
    virtual oA::Uint addCube(const oA::CubeContext &ctx);
    virtual oA::Uint addCamera(const oA::CameraContext &ctx);
    virtual oA::Uint addModel(const oA::ModelContext &ctx);
    virtual oA::Uint addAnimatedModel(const oA::ModelContext &ctx);
    virtual void applyAnimation(oA::Uint node, const oA::Animation3D &anim);
    virtual oA::V3f getNodePosition(oA::Uint node) const;
    virtual oA::V3f getNodeRotation(oA::Uint node) const;

private:
    oA::Vector<IrrlichtContext> _ctxs; // Context list
    oA::Unique<EventHandler> _handler; // EventHandler instance
    oA::Uint _idx = 0; // Context index

    /* Utils */
    IrrlichtContext &context(void);
    const IrrlichtContext &context(void) const;
    /* 2D Utils */
    irr::gui::IGUIFont *getFont(const oA::String &path);
    irr::video::ITexture *getTexture(const oA::String &path);
    irr::core::recti toRect(const oA::ItemContext &ctx) const noexcept;
    /* 3D Utils */
    irr::scene::IMesh *getMesh(const oA::String &path);
    irr::scene::IAnimatedMesh *getAnimatedMesh(const oA::String &path);
    oA::Uint insertNode(irr::scene::ISceneNode *node);
    irr::scene::ISceneNode *getNode(oA::Uint node);
    const irr::scene::ISceneNode *getNode(oA::Uint node) const;
};
