#include <irrlicht.h>
#include "enviroment/Terrain.h"
#include "enviroment/Sky.h"
#include "hud/hud.h"
#include "game/player.h"

using namespace irr;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look at them, you can
read a detailed description of them in the documentation by clicking on the top
menu item 'Namespace List' or by using this link:
http://irrlicht.sourceforge.net/docu/namespaces.html
Like the irr namespace, we do not want these 5 sub namespaces now, to keep this
example simple. Hence, we tell the compiler again that we do not want always to
write their names.
*/


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
/*
@TODO
Main Game class with all 3 main irrlicht classes(device,video,scene) to optimize code inside main()
Optimize Player class
Need a GameManager class and a Application class ----- further update


*/
int main() {

    IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(800,600),16, false,false,false,0);
    device->getCursorControl()->setVisible(false);
    video::IVideoDriver* driver = device->getVideoDriver();
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
    scene::ISceneManager* smgr = device->getSceneManager();

    core::stringw pathTexture[2] = {"media/terrain/grass_green_old.jpg","media/terrain/grass_green_thin.jpg"};
    Terrain* terrain = new Terrain(smgr,driver,pathTexture,core::vector3df(250.f,0.0001f, 250.f));
    Sky* sky = new Sky(smgr,driver,"media/terrain/sky.jpg",1000.0f);
    HUD::HUD* hud = new HUD::HUD(device,driver);

    Player* player = new Player(device,smgr,driver,terrain->getCenter(), Player::HUMAN);

    terrain->collisionResponseAnimator(smgr,player->getNode());
//    smgr->addCameraSceneNodeFPS()->setPosition(terrain->getCenter());

//    terrain->addCollisionNode(smgr,);
//    scene::ISceneCollisionManager* csmgr = smgr->getSceneCollisionManager();
    smgr->setAmbientLight(video::SColor(0,255,255,204));
    int lastFPS = -1;

    while(device->run() && device) {

        if(device->isWindowActive()){

            driver->beginScene(true, true, video::SColor(255,200,200,200));
            smgr->drawAll();
            hud->env->drawAll();
                            player->loop();

            driver->endScene();
            int fps = driver->getFPS();
            if(lastFPS != fps)
            {
                core::stringw str =L"Castle Battle [";
                str += driver->getName();
                str += "] FPS:";
                str += fps;
                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        } else
            device->yield();
    }
}

//    IAnimatedMesh* map_mesh = smgr->getMesh("./media/Second.obj");
//    ISceneNode* map_node = 0;
//
//    if(map_mesh) map_node = smgr->addOctreeSceneNode(map_mesh->getMesh(0), 0, -1, 1024);
//    if(map_node) map_node->setPosition(core::vector3df(0,-5,0));
//
//    map_node->setMaterialTexture(0,driver->getTexture("./media/FirstMap.png"));
//    //ILightSceneNode* light = smgr->addLightSceneNode(0, core::vector3df(400,800,-1400),video::SColor(0,255,255,204),2000.0f);
//    smgr->setAmbientLight(video::SColor(0,255,255,204));
