/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Irrlicht
*/

// Irrlicht
#include "Irrlicht.hpp"

void Irrlicht::clearScene(oA::Uint index)
{
    context(index).manager->clear();
}

void Irrlicht::addCamera(const oA::CameraContext &ctx, oA::Uint index)
{
    context(index).manager->addCameraSceneNode(
        nullptr,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.lookAt.x, ctx.lookAt.y, ctx.lookAt.z)
    );
}

void Irrlicht::addCube(const oA::CubeContext &ctx, oA::Uint index)
{
    auto &wnd = context(index);
    auto cube = wnd.manager->addCubeSceneNode(
        ctx.size,
        nullptr,
        -1,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.rotation.x, ctx.rotation.y, ctx.rotation.z)
    );
    cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    cube->setMaterialTexture(0, wnd.driver->getTexture(ctx.texture.c_str()));
}
