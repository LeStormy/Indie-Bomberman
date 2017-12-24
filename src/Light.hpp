/**
 * @Author: raph
 * @Date:   2017-06-14T00:10:50+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T14:04:52+02:00
 */



/*
** Light.hpp for IndieStudio
**
** Made by alexis
** Login    <alexis.chiche@epitech.net>
**
** Started on lun. juin 12 19:11:00 2017 Alexis
** Last update lun. juin 12 19:11:00 2017 Alexis
*/

#ifndef INDIESTUDIO_LIGHT_HPP
#define INDIESTUDIO_LIGHT_HPP

#include <vector>

#include "Indie.hpp"

class Light
{
  private:
    enum LIGHT_TYPE {
      MAIN_LIGHT,
      LIGHT_ENFORCEMENT
    };

  public:
    Light() = default;
    ~Light() = default;

    void 	init();
    void	clear();
    void 	lightOnScene(bool status = true);

    int 	addBasicLight(const vector3df pos = {0, 0, 0},
			     const video::SColorf ambient = {0.1f, 0.1f, 0.1f, 1},
			     const video::SColorf specular = {0.4f, 0.4f, 0.4f, 1},
			     const video::SColorf diffuse = {1.0f, 1.0f, 1.0f, 1});

    int 	addSpotLight(const vector3df pos = {5, 2, 5},
			    f32 innerCone = 1.0f, f32 outerCone = 20.0f, f32 fallOf = 1.0f,
			    const video::SColorf ambient = {0.1f, 0.1f, 0.1f, 1},
			    const video::SColorf specular = {0.4f, 0.4f, 0.4f, 1},
			    const video::SColorf diffuse = {1.0f, 1.0f, 1.0f, 1},
          const vector3df rot = {90, 0, 0});

    int 	addRotatingLight(const vector3df pos = {0, 0, 0},
				const f32 radius = 2.0f, f32 speed = 0.001f,
				const video::SColorf ambient = {0.1f, 0.1f, 0.1f, 1},
				const video::SColorf specular = {0.4f, 0.4f, 0.4f, 1},
				const video::SColorf diffuse = {1.0f, 1.0f, 1.0f, 1});

    void setVisibility(bool state, size_t lightId = 2);

    void setMapAffectedSize(const std::pair<size_t, size_t> &mapSize);

  private:
    std::vector<ILightSceneNode *> 	_lightNode;
};

#endif //INDIESTUDIO_LIGHT_HPP
