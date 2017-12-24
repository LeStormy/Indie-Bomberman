/**
 * @Author: raph
 * @Date:   2017-06-08T18:38:56+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-14T18:12:11+02:00
 */

#include "Indie.hpp"
#include "InGameMenu.hpp"
#include "Core.hpp"
#include "MenuScreens.hpp"

InGameMenu::InGameMenu()
{
  ITexture* image = Core::Display.driver->getTexture(IMAGE("DarkFilter"));
  Core::Display.env->addImage(image, position2d<int>(0,0));
  Button New(IMAGE("ResumeButton"), IMAGE("ResumeButtonPressed"),
              rect<s32>(X(7),Y(2),X(13),Y(3.5)), 0);
  Button Load(IMAGE("SettingsButtonIG"), IMAGE("SettingsButtonIGPressed"),
              rect<s32>(X(7),Y(4.5),X(13),Y(6)), 1);
  Button Back(IMAGE("BackToMenuButton"), IMAGE("BackToMenuButtonPressed"),
              rect<s32>(X(7),Y(7),X(13),Y(8.5)), 2);
}

InGameMenu::~InGameMenu()
{

}
