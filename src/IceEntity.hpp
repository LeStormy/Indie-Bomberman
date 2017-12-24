//
// Created by baptiste on 6/4/17.
//

#ifndef INDIESTUDIO_ICEENTITY_HPP
#define INDIESTUDIO_ICEENTITY_HPP

#include <algorithm>
#include "AEntity.hpp"

class IceEntity : public AEntity
{
  public:
    IceEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _type = Indie::ICE_ENTITY;
      init(Indie::ICE_ENTITY, false);
    }

    virtual ~IceEntity() { _node->remove(); }

    void update() {
      std::for_each(_tile->getPlayers().begin(), _tile->getPlayers().end(),
		    [] (APlayer *ply) { if (ply) ply->addEffect(Indie::ICE_EFFECT); });
    }
};

class OilEntity : public AEntity
{
  public:
    OilEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _type = Indie::OIL_ENTITY;
      init(Indie::OIL_ENTITY, false);
    }

    virtual ~OilEntity() { _node->remove(); }

    void update() {
      std::for_each(_tile->getPlayers().begin(), _tile->getPlayers().end(),
		    [] (APlayer *ply) { if (ply) ply->addEffect(Indie::OIL_EFFECT); });
    }
};

#endif //INDIESTUDIO_ICEENTITY_HPP
