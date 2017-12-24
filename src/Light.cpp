/**
 * @Author: raph
 * @Date:   2017-06-14T00:10:50+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T14:01:37+02:00
 */



/*
** Light.cpp for IndieStudio
**
** Made by alexis
** Login    <alexis.chiche@epitech.net>
**
** Started on lun. juin 12 19:11:00 2017 Alexis
** Last update lun. juin 12 19:11:00 2017 Alexis
*/

#include "Core.hpp"
#include "Light.hpp"

void Light::clear()
{
	_lightNode.clear();
}

void Light::init()
{
  SLight 	light_data;

  this->_lightNode.push_back(Core::Display.smgr->addLightSceneNode());
  this->_lightNode.push_back(Core::Display.smgr->addLightSceneNode());

  light_data.AmbientColor = video::SColorf(0.1f,0.1f,0.1f,1);
  light_data.SpecularColor = video::SColorf(0.4f,0.4f,0.4f,1);
  light_data.DiffuseColor = video::SColorf(1.0f,1.0f,1.0f,1);
  light_data.Direction = {0, 0, 0};
  light_data.CastShadows = true;

  light_data.Type = ELT_POINT;
  this->_lightNode[MAIN_LIGHT]->setLightData(light_data);
  this->_lightNode[LIGHT_ENFORCEMENT]->setLightData(light_data);

  this->_lightNode[MAIN_LIGHT]->setVisible(false);
  this->_lightNode[LIGHT_ENFORCEMENT]->setVisible(false);
}

void Light::setMapAffectedSize(const std::pair<size_t, size_t> &mapSize)
{
  _lightNode[MAIN_LIGHT]->setPosition({static_cast<f32>(mapSize.first) / 2.0f , 5.0f, static_cast<f32>(mapSize.second) / 2.0f});
  _lightNode[LIGHT_ENFORCEMENT]->setPosition({static_cast<f32>(mapSize.first) / 2.0f, 5.0f, static_cast<f32>(mapSize.second) / 2.0f});
}

void Light::lightOnScene(bool status)
{
  if (status) {
    this->_lightNode[MAIN_LIGHT]->setVisible(true);
    this->_lightNode[LIGHT_ENFORCEMENT]->setVisible(true);
  } else {
    this->_lightNode[MAIN_LIGHT]->setVisible(false);
    this->_lightNode[LIGHT_ENFORCEMENT]->setVisible(false);
  }
}

void Light::setVisibility(bool state, size_t lightId) {
  if (lightId >= _lightNode.size())
    return ;
  _lightNode[lightId]->setVisible(state);
}

int 	Light::addBasicLight(const vector3df pos,
			 const video::SColorf ambient,
			 const video::SColorf specular,
			 const video::SColorf diffuse)
{
  SLight	lightData;

  if (_lightNode.size() < 8)
    return (-1);
  _lightNode.push_back(Core::Display.smgr->addLightSceneNode());

  lightData.AmbientColor = ambient;
  lightData.SpecularColor = specular;
  lightData.DiffuseColor = diffuse;
  lightData.Type = ELT_POINT;

  _lightNode.back()->setPosition(pos);
  _lightNode.back()->setVisible(true);
  _lightNode.back()->setLightData(lightData);

  return (_lightNode.size() - 1);
}

int 	Light::addSpotLight(const vector3df pos,
			f32 innerCone, f32 outerCone, f32 fallOf,
			const video::SColorf ambient,
			const video::SColorf specular,
			const video::SColorf diffuse,
      vector3df rot)
{
  SLight	lightData;

  if (_lightNode.size() >= 8)
    return (-1);
  _lightNode.push_back(Core::Display.smgr->addLightSceneNode());

  lightData.AmbientColor = ambient;
  lightData.SpecularColor = specular;
  lightData.DiffuseColor = diffuse;
  lightData.Type = ELT_SPOT;
  lightData.InnerCone = innerCone;
  lightData.OuterCone = outerCone;
  lightData.Falloff = fallOf;

  _lightNode.back()->setPosition(pos);
  _lightNode.back()->setLightData(lightData);
  _lightNode.back()->setRotation(rot);
  _lightNode.back()->setVisible(true);

  return (_lightNode.size() - 1);
}

int 	Light::addRotatingLight(const vector3df pos,
			    const f32 radius, f32 speed,
			    const video::SColorf ambient,
			    const video::SColorf specular,
			    const video::SColorf diffuse)
{
  SLight	lightData;
  scene::ISceneNodeAnimator* animator = nullptr;

  if (_lightNode.size() >= 8)
    return (-1);
  _lightNode.push_back(Core::Display.smgr->addLightSceneNode());

  lightData.AmbientColor = ambient;
  lightData.SpecularColor = specular;
  lightData.DiffuseColor = diffuse;
  lightData.Type = ELT_POINT;

  _lightNode.back()->setPosition({5, 0, 5});
  animator = Core::Display.smgr->createFlyCircleAnimator(pos, radius, speed);
  _lightNode.back()->addAnimator(animator);
  animator->drop();

  _lightNode.back()->setVisible(true);
  _lightNode.back()->setLightData(lightData);

  return (_lightNode.size() - 1);
}
