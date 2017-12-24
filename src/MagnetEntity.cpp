//
// Created by baptiste on 6/11/17.
//

#include "MagnetEntity.hpp"

MagnetEntity::MagnetEntity(Tile &tile, APlayer *player, int dir) {
  _tile = &tile;
  _player = player;
  _type = Indie::MAGNET_ENTITY;
  _tile->setReachable(false);
  if (dir == -1 || dir > 3)
    _direction = static_cast<Indie::Direction>(std::rand() % 4);
  else
    _direction = static_cast<Indie::Direction>(dir);
  init(Indie::MAGNET_ENTITY);
  switch (_direction) {
    case Indie::UP_DIRECTION:
      _node->setRotation({0, 180, 0});
      break ;
    case Indie::RIGHT_DIRECTION:
      _node->setRotation({0, 270, 0});
      break ;
    case Indie::DOWN_DIRECTION:
      _node->setRotation({0, 0, 0});
      break ;
    case Indie::LEFT_DIRECTION:
      _node->setRotation({0, 90, 0});
      break ;
    default:
      break ;
  }
}

void 		MagnetEntity::update()
{
  Tile 		*tmpTile;
  AEntity	*tmpEnt;

  tmpTile = _tile;
  _tile->setReachable(false);
  switch (_direction) {
    case Indie::UP_DIRECTION:
      while ((tmpTile = tmpTile->getMapHandler()->getTile<Indie::UP_DIRECTION>(tmpTile)) != nullptr &&
	     tmpTile->crossEntity(Indie::MAGNET_ENTITY) && tmpTile->getPos().Y == _tile->getPos().Y)
	if ((tmpEnt = tmpTile->getEntityIfOn(Indie::BOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::FROZENBOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::OILBOMB_ENTITY)))
	  tmpEnt->addMovement(Indie::STRAFE_DOWN_MOV);
      break;
    case Indie::DOWN_DIRECTION:
      while ((tmpTile = tmpTile->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(tmpTile)) != nullptr &&
	     tmpTile->crossEntity(Indie::MAGNET_ENTITY) && tmpTile->getPos().Y == _tile->getPos().Y)
	if ((tmpEnt = tmpTile->getEntityIfOn(Indie::BOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::FROZENBOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::OILBOMB_ENTITY)))
	  tmpEnt->addMovement(Indie::STRAFE_UP_MOV);
      break;
    case Indie::RIGHT_DIRECTION:
      while ((tmpTile = tmpTile->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(tmpTile)) != nullptr &&
	     tmpTile->crossEntity(Indie::MAGNET_ENTITY) && tmpTile->getPos().Y == _tile->getPos().Y)
	if ((tmpEnt = tmpTile->getEntityIfOn(Indie::BOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::FROZENBOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::OILBOMB_ENTITY)))
	  tmpEnt->addMovement(Indie::STRAFE_LEFT_MOV);
      break;
    case Indie::LEFT_DIRECTION:
      while ((tmpTile = tmpTile->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(tmpTile)) != nullptr &&
	     tmpTile->crossEntity(Indie::MAGNET_ENTITY) && tmpTile->getPos().Y == _tile->getPos().Y)
	if ((tmpEnt = tmpTile->getEntityIfOn(Indie::BOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::FROZENBOMB_ENTITY)) ||
	    (tmpEnt = tmpTile->getEntityIfOn(Indie::OILBOMB_ENTITY)))
	  tmpEnt->addMovement(Indie::STRAFE_RIGHT_MOV);
      break;
    default:
      break ;
  }
}

void 		MagnetEntity::onFlameHit()
{
  switch (_direction)
  {
    case Indie::UP_DIRECTION:
      _direction = Indie::RIGHT_DIRECTION;
      _node->setRotation({0,270, 0});
      break;
    case Indie::DOWN_DIRECTION:
      _direction = Indie::LEFT_DIRECTION;
      _node->setRotation({0, 90, 0});
      break;
    case Indie::RIGHT_DIRECTION:
      _direction = Indie::DOWN_DIRECTION;
      _node->setRotation({0, 0, 0});
      break;
    case Indie::LEFT_DIRECTION:
      _direction = Indie::UP_DIRECTION;
      _node->setRotation({0, 180, 0});
      break;
    default:
      break ;
  }
}