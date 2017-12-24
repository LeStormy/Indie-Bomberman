//
// Created by baptiste on 6/11/17.
//

#ifndef INDIESTUDIO_MAGNETENTITY_HPP
#define INDIESTUDIO_MAGNETENTITY_HPP

#include "AEntity.hpp"
#include "Tile.hpp"
#include "MapHandler.hpp"
#include "APlayer.hpp"

class MagnetEntity : public AEntity
{
  private:
    Indie::Direction 	_direction;
  public:
    MagnetEntity(Tile &tile, APlayer *player, int dir = -1);
    virtual ~MagnetEntity() = default;

    virtual void 	onFlameHit();

    virtual void	update();
};

#endif //INDIESTUDIO_MAGNETENTITY_HPP
