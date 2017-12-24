//
// Created by baptiste on 6/4/17.
//

#ifndef INDIESTUDIO_UNBREAKABLEENTITY_HPP
#define INDIESTUDIO_UNBREAKABLEENTITY_HPP

#include "AEntity.hpp"
#include "Tile.hpp"

class UnbreakableEntity : public AEntity
{
  public:
    UnbreakableEntity(Tile &tile, APlayer *player, bool border)
    {
      _tile = &tile;
      _player = player;
      _tile->setReachable(false);
      if (border)
	init(Indie::UNBREAKABLE_BORDER_ENTITY);
      else
	init(Indie::UNBREAKABLE_ENTITY);
    }

    virtual ~UnbreakableEntity()
    {
      _node->remove();
    }

    bool 	operator==(const Indie::Entity type) { return type == Indie::UNBREAKABLE_ENTITY; }

    void update() {}
};

#endif //INDIESTUDIO_UNBREAKABLEENTITY_HPP
