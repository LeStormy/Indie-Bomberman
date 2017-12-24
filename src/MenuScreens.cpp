/**
 * @Author: Raphael Betrand <raph>
 * @Date: 2017-05-16T13:34:56+02:00
 * @Email:raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:09:03+02:00
 */

#include <irrlicht/irrlicht.h>
#include "MenuScreens.hpp"
#include "Menu.hpp"
#include "Text.hpp"
#include "CGUITTFont.h"
#include "MeshPathGetter.hpp"
#include "Indie.hpp"

///////////

SplashScreen::SplashScreen()
{

}

void SplashScreen::sceneSetter(const Settings &)
{
 IAnimatedMeshSceneNode *node;
 ITexture *texture;
 if (!(node = Core::Display.smgr->addAnimatedMeshSceneNode(Core::Display.smgr->getMesh(MESH("SplashScreen/SplashScreen.3ds"))))
     || !(texture = Core::Display.driver->getTexture(MESH("SplashScreen/AllBombermanColorPattern.png"))))
   return ;
 node->setMaterialTexture(0, texture);
 Core::Display.light.init();
 Core::Display.light.lightOnScene(true);
 Core::Display.light.setMapAffectedSize(std::pair<size_t,size_t>(20,20));
 Core::Display.light.addRotatingLight({1.0f, 2.0f, 1.0f}, 30.0f);
 Core::Display.light.addSpotLight(vector3df(0,-5,0),
                                  1.0f, 30.0f, 1.0f, SColorf(1,1,1,1),SColorf(1,1,1,1),SColorf(1,1,1,1));
}

///
///////////////////////////////////////////////////
///

void MainScreen::sceneSetter(const Settings &)
{
  ITexture* image = Core::Display.driver->getTexture(IMAGE("MainMenuBackground"));
  Core::Display.env->addImage(image, position2d<int>(0,0));
  Button Play(IMAGE("PlayButton"), IMAGE("PlayButtonPressed"),
              rect<s32>(X(8),Y(2.5),X(20),Y(3.5)), Indie::MenuButtons::SETGAME_BUTTON);
  Button Score(IMAGE("ScoreButton"), IMAGE("ScoreButtonPressed"),
              rect<s32>(X(8),Y(4),X(20),Y(5)), Indie::MenuButtons::SCOREBOARD_BUTTON);
  Button Settings(IMAGE("SettingsButton"), IMAGE("SettingsButtonPressed"),
              rect<s32>(X(8),Y(5.5),X(20),Y(6.5)), Indie::MenuButtons::OPTIONS_BUTTON);
  Button Exit(IMAGE("ExitButton"), IMAGE("ExitButtonPressed"),
              rect<s32>(X(8),Y(7),X(20),Y(8)), Indie::MenuButtons::QUIT_BUTTON);
}
