//
// Created by wurtz on 6/5/17.
//

#include "TrampolineEntity.hpp"
#include "MovementManager.hpp"

TrampolineEntity::TrampolineEntity(Tile &tile, APlayer *player)
{
  _tile = &tile;
  _player = player;
  _type = Indie::TRAMPOLINE_ENTITY;
  init(Indie::TRAMPOLINE_ENTITY, false);
}

TrampolineEntity::~TrampolineEntity() { _node->remove(); }

void TrampolineEntity::update()
{
  AEntity	*tmpEnt;

  for (auto &it : _tile->getPlayers())
    if (it != nullptr)
    {
      if (it->getDirection() == Indie::UP_DIRECTION &&
	getTile()->getMapHandler()->getTile<Indie::UP_DIRECTION>(getTile())->getReachable())
	it->addMovement(Indie::JUMP_UP_MOV);

      else if (it->getDirection() == Indie::DOWN_DIRECTION &&
	       getTile()->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(getTile())->getReachable())
	it->addMovement(Indie::JUMP_DOWN_MOV);

      else if (it->getDirection() == Indie::LEFT_DIRECTION &&
	       getTile()->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(getTile())->getReachable())
	it->addMovement(Indie::JUMP_LEFT_MOV);

      else if (it->getDirection() == Indie::RIGHT_DIRECTION &&
	       getTile()->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(getTile())->getReachable())
	it->addMovement(Indie::JUMP_RIGHT_MOV);
    }

  if ((tmpEnt = getTile()->getEntityIfOn(Indie::BOMB_ENTITY)) != nullptr)
  {
    if (tmpEnt->getDirection() == Indie::UP_DIRECTION &&
	getTile()->getMapHandler()->getTile<Indie::UP_DIRECTION>(getTile())->checkAddEntity(Indie::BOMB_ENTITY))
      tmpEnt->addMovement(Indie::JUMP_UP_MOV);

    else if (tmpEnt->getDirection() == Indie::DOWN_DIRECTION &&
	    getTile()->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(getTile())->checkAddEntity(Indie::BOMB_ENTITY))
    tmpEnt->addMovement(Indie::JUMP_DOWN_MOV);

    else if (tmpEnt->getDirection() == Indie::LEFT_DIRECTION &&
	     getTile()->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(getTile())->checkAddEntity(Indie::BOMB_ENTITY))
      tmpEnt->addMovement(Indie::JUMP_LEFT_MOV);

    else if (tmpEnt->getDirection() == Indie::RIGHT_DIRECTION &&
	     getTile()->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(getTile())->checkAddEntity(Indie::BOMB_ENTITY))
      tmpEnt->addMovement(Indie::JUMP_RIGHT_MOV);
  }
}
