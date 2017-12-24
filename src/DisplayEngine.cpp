/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-18T15:05:27+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-17T14:42:28+02:00
 */

#include "Core.hpp"

Indie::SwitchDisplay DisplayEngine::dSwitch = Indie::TO_MENU;
Indie::DisplayInstance DisplayEngine::dInstance = Indie::MENU;

DisplayEngine::DisplayEngine()
{

}

void DisplayEngine::initAll() {
  IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
  Core::Resolution = nulldevice->getVideoModeList()->getDesktopResolution();
  nulldevice->drop();

  this->device = createDevice(irr::video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16, true, true);
  this->driver = this->device->getVideoDriver();

  this->env = this->device->getGUIEnvironment();
  this->skin = this->env->getSkin();
  this->smgr = this->device->getSceneManager();
}

void DisplayEngine::render() {
  driver->beginScene(true, true, SColor(0, 0, 0, 0));
  smgr->drawAll();
  env->drawAll();
  driver->endScene();
}
