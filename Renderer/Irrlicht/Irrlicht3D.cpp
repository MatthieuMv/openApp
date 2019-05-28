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
        getMesh(ctx.mesh),
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

void Irrlicht::applyAnimation(oA::Uint node, const oA::Animation3D &anim)
{
    auto &wnd = context();

    if (node > wnd.maxNodeIdx)
        throw oA::LogicError("Irrlicht", "Scene node index @out of range@");
    auto n = wnd.nodes[node];
    anim.visit(oA::Overload{
        [n](const oA::PositionAnim &anim) {
            n->setPosition(irr::core::vector3df(anim.pos.x, anim.pos.y, anim.pos.z));
        },
        [n](const oA::MovementAnim &anim) {
            auto pos = n->getPosition();
            pos.X += anim.move.x;
            pos.Y += anim.move.y;
            pos.Z += anim.move.z;
            n->setPosition(pos);
        },
        [n](const oA::RotationAnim &anim) {
            n->setRotation(irr::core::vector3df(anim.rotation.x, anim.rotation.y, anim.rotation.z));
        },
        [n](const oA::MeshAnim &anim) {
            auto nMesh = dynamic_cast<irr::scene::IAnimatedMeshSceneNode *>(n);
            if (!nMesh)
                throw oA::LogicError("Irrlicht::AnimationVisitor", "Target not is not an @animated mesh@");
            nMesh->setFrameLoop(anim.from, anim.to);
            nMesh->setAnimationSpeed(anim.speed);
        }
    });
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