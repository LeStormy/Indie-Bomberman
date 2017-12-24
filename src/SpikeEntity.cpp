//
// Created by wurtz on 6/5/17.
//

#include "SpikeEntity.hpp"
#include "APlayer.hpp"
#include "Core.hpp"

SpikeEntity::SpikeEntity(Tile &tile, APlayer *player)
{
  _tile = &tile;
  _player = player;
  _timer = 0;
  init(Indie::SPIKE_ENTITY, false);
}

SpikeEntity::~SpikeEntity()
{
}

void			SpikeEntity::update()
{
  if ((_timer = fmod(_timer + Core::frameRate, static_cast<float>(5))) <= 2)
  {
    std::for_each(_tile->getPlayers().begin(), _tile->getPlayers().end(), [] (APlayer *ply) { ply ? ply->killMe() : (void)ply; });
    _tile->deleteEntities(_tile->getDeleteEntityRule(Indie::SPIKE_ENTITY));
    _node->setScale(vector3df(1,3,1));
    _tile->setTimeToDie(0);
  }
  else
  {
    _node->setScale(vector3df(1,1,1));
    if (_tile->getTimeToDie() <= 0)
      _tile->setTimeToDie(3);
    _tile->setTimeToDie(_tile->getTimeToDie() - Core::frameRate);
  }
}
