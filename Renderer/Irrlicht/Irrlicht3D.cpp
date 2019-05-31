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
    auto &wnd = context();

    wnd.maxNodeIdx = 0;
    wnd.nodes.clear();
    wnd.manager->clear();
}

void Irrlicht::drawScene(void)
{
    context().manager->drawAll();
}

oA::Uint Irrlicht::addCamera(const oA::CameraContext &ctx)
{
    auto camera = context().manager->addCameraSceneNode(
        nullptr,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.lookAt.x, ctx.lookAt.y, ctx.lookAt.z)
    );
    return insertNode(camera);
}

oA::Uint Irrlicht::addCube(const oA::CubeContext &ctx)
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
    return insertNode(cube);
}

oA::Uint Irrlicht::addModel(const oA::ModelContext &ctx)
{
    auto model = context().manager->addMeshSceneNode(
        getAnimatedMesh(ctx.mesh),
        nullptr,
        -1,
        irr::core::vector3df(ctx.pos.x, ctx.pos.y, ctx.pos.z),
        irr::core::vector3df(ctx.rotation.x, ctx.rotation.y, ctx.rotation.z),
        irr::core::vector3df(ctx.scale.x, ctx.scale.y, ctx.scale.z)
    );
    model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    if (!ctx.texture.empty())
        model->setMaterialTexture(0, getTexture(ctx.texture.c_str()));
    return insertNode(model);
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
    if (!ctx.texture.empty())
        model->setMaterialTexture(0, getTexture(ctx.texture.c_str()));
    return insertNode(model);
}

void Irrlicht::removeSceneNode(oA::Uint node)
{
    auto &wnd = context();
    wnd.manager->addToDeletionQueue(getNode(node));
    wnd.nodes.erase(node);
}

void Irrlicht::moveNode(oA::Uint node, const oA::V3f &move)
{
    auto n = getNode(node);
    auto pos = n->getPosition();

    pos.X += move.x;
    pos.Y += move.y;
    pos.Z += move.z;
    n->setPosition(pos);
}

void Irrlicht::setNodePosition(oA::Uint node, const oA::V3f &position)
{
    auto n = getNode(node);
    irr::core::vector3df res;

    res.X = position.x;
    res.Y = position.y;
    res.Z = position.z;
    n->setPosition(res);
}

void Irrlicht::setNodeRotation(oA::Uint node, const oA::V3f &rotation)
{
    auto n = getNode(node);
    irr::core::vector3df res;

    res.X = rotation.x;
    res.Y = rotation.y;
    res.Z = rotation.z;
    n->setRotation(res);
}

void Irrlicht::setNodeScale(oA::Uint node, const oA::V3f &scale)
{
    auto n = getNode(node);
    irr::core::vector3df res;

    res.X = scale.x;
    res.Y = scale.y;
    res.Z = scale.z;
    n->setScale(res);
}

void Irrlicht::setNodeAnimation(oA::Uint node, oA::Uint from, oA::Uint to, oA::Uint speed)
{
    auto n = getNode(node);
    auto *nMesh = (irr::scene::IAnimatedMeshSceneNode *)(n);

    if (!nMesh)
        throw oA::LogicError("Irrlicht::AnimationVisitor", "Target not is not an @animated mesh@");
    nMesh->setFrameLoop(from, to);
    nMesh->setAnimationSpeed(speed);
}

oA::V3f Irrlicht::getNodePosition(oA::Uint node) const
{
    auto n = getNode(node);
    const auto &r = n->getPosition();

    return oA::V3f(r.X, r.Y, r.Z);
}

oA::V3f Irrlicht::getNodeRotation(oA::Uint node) const
{
    auto n = getNode(node);
    const auto &r = n->getRotation();

    return oA::V3f(r.X, r.Y, r.Z);
}

oA::V3f Irrlicht::getNodeScale(oA::Uint node) const
{
    auto n = getNode(node);
    const auto &r = n->getScale();

    return oA::V3f(r.X, r.Y, r.Z);
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

oA::Uint Irrlicht::insertNode(irr::scene::ISceneNode *node)
{
    auto &wnd = context();
    ++wnd.maxNodeIdx;
    wnd.nodes[wnd.maxNodeIdx] = node;
    return wnd.maxNodeIdx;
}

irr::scene::ISceneNode *Irrlicht::getNode(oA::Uint node)
{
    auto &wnd = context();
    auto it = wnd.nodes.find(node);

    if (it == wnd.nodes.end())
        throw oA::AccessError("Irrlicht", "Node index @out of range@");
    return (it->second);
}

const irr::scene::ISceneNode *Irrlicht::getNode(oA::Uint node) const
{
    auto &wnd = context();
    auto it = wnd.nodes.find(node);

    if (it == wnd.nodes.end())
        throw oA::AccessError("Irrlicht", "Node index @out of range@");
    return (it->second);
}
