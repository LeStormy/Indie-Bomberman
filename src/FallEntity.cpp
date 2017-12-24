//
// Created by wurtz on 6/18/17.
//

#include "FallEntity.hpp"
#include "APlayer.hpp"
#include "Core.hpp"

FallEntity::FallEntity(Tile &tile, APlayer *player)
{
  _tile = &tile;
  _player = player;
  init(Indie::FALL_ENTITY, false);
  _node->setFrameLoop(1, 100);
  _tile->setReachable(false);
  _tile->setTimeToDie(0.3f);
}

FallEntity::~FallEntity()
{
}

void			FallEntity::update()
{
  if (_node->getFrameNr() > 18)
  {
    _node->setFrameLoop(40, 90);
    _tile->deleteEntities(_tile->getDeleteEntityRule(Indie::FALL_ENTITY));
    std::for_each(_tile->getPlayers().begin(), _tile->getPlayers().end(), [] (APlayer *ply) { ply ? ply->killMe(true) : (void)ply; });
  }
}
