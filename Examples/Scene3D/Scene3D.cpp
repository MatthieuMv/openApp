/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IrrlichtMain
*/

#include "IrrlichtApp.hpp"
#include "openApp.hpp"

class MyScene : public oA::Scene3D
{
public:
    MyScene(void) {}

    virtual ~MyScene(void) {}

    virtual oA::String getName(void) const noexcept { return "MyScene"; }

    virtual void draw3D(oA::IRenderer3D &renderer) {
        if (_reloadMap)
            reloadMap(renderer);
    }

private:
    bool _reloadMap = true;

    void reloadMap(oA::IRenderer3D &renderer) {
        oA::cout << "#Loading# @map@" << oA::endl;
        renderer.clearScene();
        {
            oA::CameraContext cam;
            cam.pos.x = 0;
            cam.pos.y = 300;
            cam.pos.z = -600;
            renderer.addCamera(cam);
        }
        {
            oA::CubeContext ctx;
            ctx.size = 50;
            ctx.texture = "cube.png";
            for (auto y = -5; y <= 5; ++y) {
                for (auto x = -5; x <= 5; ++x) {
                    ctx.pos.x = x * ctx.size;
                    ctx.pos.z = y * ctx.size;
                    renderer.addCube(ctx);
                }
            }
        }
        {
            oA::ModelContext ctx;
            ctx.pos.z = 50;
            ctx.scale = oA::V3f(100, 100, 100);
            ctx.mesh = "mesh.b3d";
            //ctx.texture = "PlayerColorSetOne.png";
            renderer.addModel(ctx);
        }
        _reloadMap = false;
    }
};

int main(void)
{
    try {
        oA::IrrlichtApp app(true);

        oA::AppFactory::Register<MyScene>();
        app.parseFile("Scene3D.oA");
        app.run();
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}