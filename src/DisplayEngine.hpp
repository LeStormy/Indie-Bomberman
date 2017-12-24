/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-18T15:04:28+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-13T15:19:14+02:00
 */

#ifndef DISPLAYENGINE_HPP
# define DISPLAYENGINE_HPP

#include "Indie.hpp"
#include "Light.hpp"
#include "Camera.hpp"

class DisplayEngine {
public:
  DisplayEngine();
  ~DisplayEngine() {}

  static Indie::SwitchDisplay dSwitch;
  static Indie::DisplayInstance dInstance;

  void initAll();
  void freeAll() { this->device->drop(); }
  void render();

//private:
  IrrlichtDevice *  device;
  IVideoDriver *  driver;
  IGUIEnvironment *  env;
  IGUISkin *  skin;
  ISceneManager *  smgr;
  Light 	light;
  CameraManager  camera;

  private:
};

#endif
