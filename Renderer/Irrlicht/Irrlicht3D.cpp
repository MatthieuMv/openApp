/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Irrlicht
*/

// Irrlicht
#include "Irrlicht.hpp"

void Irrlicht::clearScene(void)
{
    context().manager->clear();
}

void Irrlicht::addCamera(const oA::CameraContext &ctx)
{
    context().manager->addCameraSceneNode(
        nullptr,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.lookAt.x, ctx.lookAt.y, ctx.lookAt.z)
    );
}

void Irrlicht::addCube(const oA::CubeContext &ctx)
{
    auto cube = context().manager->addCubeSceneNode(
        ctx.size,
        nullptr,
        -1,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.rotation.x, ctx.rotation.y, ctx.rotation.z),
        irr::core::vector3df(ctx.scale.x, ctx.scale.y, ctx.scale.z)
    );
    cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    cube->setMaterialTexture(0, getTexture(ctx.texture.c_str()));
}

void Irrlicht::addModel(const oA::ModelContext &ctx)
{
    auto model = context().manager->addMeshSceneNode(getMesh(ctx.mesh),
        nullptr,
        -1,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.rotation.x, ctx.rotation.y, ctx.rotation.z),
        irr::core::vector3df(ctx.scale.x, ctx.scale.y, ctx.scale.z)
    );
    model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    model->setMaterialTexture(0, getTexture(ctx.texture.c_str()));
}

oA::Uint Irrlicht::addAnimatedModel(const oA::ModelContext &ctx)
{
    auto model = context().manager->addAnimatedMeshSceneNode(
        getAnimatedMesh(ctx.mesh),
        nullptr,
        -1,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.rotation.x, ctx.rotation.y, ctx.rotation.z),
        irr::core::vector3df(ctx.scale.x, ctx.scale.y, ctx.scale.z)
    );
    model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    model->setMaterialTexture(0, getTexture(ctx.texture.c_str()));
    return 0;
}

irr::scene::IMesh *Irrlicht::getMesh(const oA::String &path)
{
    auto mesh = context().manager->getMesh(path.c_str());
    if (!mesh)
        throw oA::RuntimeError("Irrlicht", "Couldn't load mesh @" + path + "@");
    return mesh;
}

irr::scene::IAnimatedMesh *Irrlicht::getAnimatedMesh(const oA::String &path)
{
    auto mesh = context().manager->getMesh(path.c_str());
    if (!mesh)
        throw oA::RuntimeError("Irrlicht", "Couldn't load mesh @" + path + "@");
    return mesh;
}