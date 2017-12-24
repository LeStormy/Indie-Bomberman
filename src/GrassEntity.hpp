//
// Created by wurtz on 6/4/17.
//

#ifndef INDIESTUDIO_GRASSENTITY_HPP
#define INDIESTUDIO_GRASSENTITY_HPP

#include "AEntity.hpp"

class GrassEntity : public AEntity
{
  public:
    GrassEntity(Tile &tile, APlayer *player)
    {
      _tile = &tile;
      _player = player;
      _type = Indie::GROUND_ENTITY;
      init(Indie::GROUND_ENTITY, true);
    }

    virtual ~GrassEntity()
    {
    }

    void update() {}
};

#endif //INDIESTUDIO_GRASSENTITY_HPP
