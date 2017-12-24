//
// Created by baptiste on 6/8/17.
//

#ifndef INDIESTUDIO_POWERMIDDLEENTITY_HPP
#define INDIESTUDIO_POWERMIDDLEENTITY_HPP

#include <memory>
#include "Core.hpp"
#include "Tile.hpp"
#include "AEntity.hpp"
#include "Indie.hpp"

class PowerSpeedEntity : public AEntity
{
public:
  PowerSpeedEntity(Tile &tile, APlayer *)
  {
    _timer = 20;
    _tile = &tile;
    _tile->addAttractivity(40);
    _type = Indie::POWERSPEED_ENTITY;
    init(Indie::POWERSPEED_ENTITY);
    initParticlePower();
  }

  virtual ~PowerSpeedEntity()
  {
    _effects.clear();
    for (size_t i = 0; i < _ps.size(); i++)
    {
      _ps.at(i)->removeAllAffectors();
      _ps.at(i)->removeAnimators();
      _ps.at(i)->remove();
    }
    _node->remove();
  }

  void				update()
  {
    for (auto & it : _tile->getPlayers())
      if (it != nullptr) {
        it->addEffect(Indie::SPEED_EFFECT);
        _tile->deleteEntities({Indie::POWERSPEED_ENTITY});
        return ;
      }
    if ((_timer -= Core::frameRate) <= 0)
      _tile->deleteEntities({Indie::POWERSPEED_ENTITY});
  }

private:
  float 				_timer;
};

#endif //INDIESTUDIO_POWERMIDDLEENTITY_HPP
