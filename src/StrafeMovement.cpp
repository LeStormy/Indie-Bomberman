//
// Created by baptiste on 6/5/17.
//

#include "StrafeMovement.hpp"
#include "AEntity.hpp"
#include "APlayer.hpp"
#include "Tile.hpp"

void 			StrafePlayer::rotate(Indie::Direction direction)
{
  switch (direction) {
    case Indie::UP_DIRECTION:
      if (_player->getNode()->getRotation() != vector3df(0, 180, 0))
      {
	if (_player->getNode()->getRotation().Y <= 160)
	  _player->getNode()->setRotation({0, _player->getNode()->getRotation().Y + 20, 0});
	else if (_player->getNode()->getRotation().Y >= 200)
	  _player->getNode()->setRotation({0, _player->getNode()->getRotation().Y - 20, 0});
	else
	  _player->getNode()->setRotation({0, 180, 0});
      }
      break;
    case Indie::DOWN_DIRECTION:
      if (_player->getNode()->getRotation() != vector3df(0, 0, 0))
      {
	if (_player->getNode()->getRotation().Y >= 20 && _player->getNode()->getRotation().Y <= 180)
	  _player->getNode()->setRotation({0, _player->getNode()->getRotation().Y - 20, 0});
	else if (_player->getNode()->getRotation().Y > 180 && _player->getNode()->getRotation().Y <= 340)
	  _player->getNode()->setRotation({0, _player->getNode()->getRotation().Y + 20, 0});
	else
	  _player->getNode()->setRotation({0, 0, 0});
      }
      break;
    case Indie::LEFT_DIRECTION:
      if (_player->getNode()->getRotation() != vector3df(0, 90, 0))
      {
	if (_player->getNode()->getRotation().Y <= 70 || _player->getNode()->getRotation().Y >= 270)
	  _player->getNode()->setRotation({0, static_cast<float>(static_cast<int>(_player->getNode()->getRotation().Y + 20) % 360), 0});
	else if (_player->getNode()->getRotation().Y >= 110 && _player->getNode()->getRotation().Y < 270)
	  _player->getNode()->setRotation({0, _player->getNode()->getRotation().Y - 20, 0});
	else
	  _player->getNode()->setRotation({0, 90, 0});
      }
      break;
    case Indie::RIGHT_DIRECTION:
      if (_player->getNode()->getRotation() != vector3df(0, 270, 0))
      {
	if (_player->getNode()->getRotation().Y <= 250 && _player->getNode()->getRotation().Y >= 90)
	  _player->getNode()->setRotation({0, _player->getNode()->getRotation().Y + 20, 0});
	else if (_player->getNode()->getRotation().Y >= 290 || _player->getNode()->getRotation().Y < 90)
	{
	  if (_player->getNode()->getRotation().Y <= 0)
	    _player->getNode()->setRotation({0, 360, 0});
	  _player->getNode()->setRotation({0, _player->getNode()->getRotation().Y - 20, 0});
	}
	else
	  _player->getNode()->setRotation({0, 270, 0});
      }
      break;
    default :
      break ;
  }
}

bool			StrafePlayer::updateUp()
{
  if (_player->getTile()->getId() != _player->getTile()->getMapHandler()->getTile({_player->getPos().X, _player->getPos().Y, _player->getPos().Z + 0.4f})->getId() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X, _player->getPos().Y, _player->getPos().Z + 0.4f})->getReachable() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X, _player->getPos().Y, _player->getPos().Z + 0.4f})->getPos().Y < _player->getPos().Y)
  {
    _player->addMovement(Indie::JUMP_UP_MOV);
    return true;
  }

  _player->setPos({_player->getPos().X,
		   _player->getTile()->getPos().Y,
		   _player->getPos().Z + _player->getSpeed()});
  return _player->getPos().Z < _destTile->getPosCenter().Z;
}

bool			StrafePlayer::updateDown()
{
  if (_player->getTile()->getId() != _player->getTile()->getMapHandler()->getTile({_player->getPos().X, _player->getPos().Y, _player->getPos().Z - 0.4f})->getId() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X, _player->getPos().Y, _player->getPos().Z - 0.4f})->getReachable() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X, _player->getPos().Y, _player->getPos().Z - 0.4f})->getPos().Y < _player->getPos().Y)
  {
    _player->addMovement(Indie::JUMP_DOWN_MOV);
    return true;
  }

  _player->setPos({_player->getPos().X,
		   _player->getTile()->getPos().Y,
		   _player->getPos().Z - _player->getSpeed()});
  return _player->getPos().Z > _destTile->getPosCenter().Z;
}

bool			StrafePlayer::updateLeft()
{
  if (_player->getTile()->getId() != _player->getTile()->getMapHandler()->getTile({_player->getPos().X - 0.4f, _player->getPos().Y, _player->getPos().Z})->getId() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X - 0.4f, _player->getPos().Y, _player->getPos().Z})->getReachable() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X - 0.4f, _player->getPos().Y, _player->getPos().Z})->getPos().Y < _player->getPos().Y)
  {
    _player->addMovement(Indie::JUMP_LEFT_MOV);
    return true;
  }

  _player->setPos({_player->getPos().X - _player->getSpeed(),
		   _player->getTile()->getPos().Y,
		   _player->getPos().Z});
  return _player->getPos().X > _destTile->getPosCenter().X;
}

bool			StrafePlayer::updateRight()
{
  if (_player->getTile()->getId() != _player->getTile()->getMapHandler()->getTile({_player->getPos().X + 0.4f, _player->getPos().Y, _player->getPos().Z})->getId() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X + 0.4f, _player->getPos().Y, _player->getPos().Z})->getReachable() &&
      _player->getTile()->getMapHandler()->getTile({_player->getPos().X + 0.4f, _player->getPos().Y, _player->getPos().Z})->getPos().Y < _player->getPos().Y)
  {
    _player->addMovement(Indie::JUMP_RIGHT_MOV);
    return true;
  }

  _player->setPos({_player->getPos().X + _player->getSpeed(),
		   _player->getTile()->getPos().Y,
		   _player->getPos().Z});
  return _player->getPos().X < _destTile->getPosCenter().X;
}

bool			StrafePlayer::update()
{
  AEntity		*ent;

  rotate(_direction);
  if (!_destTile->getReachable() || _destTile->getPos().Y > _player->getTile()->getPos().Y){
    if (_destTile->getPos().Y == _player->getTile()->getPos().Y &&
	_player->hasBonus(Indie::KICK_EFFECT) && ((ent = _destTile->getEntityIfOn(Indie::BOMB_ENTITY)) ||
      						  (ent = _destTile->getEntityIfOn(Indie::FROZENBOMB_ENTITY)) ||
      						  (ent = _destTile->getEntityIfOn(Indie::OILBOMB_ENTITY))))
      ent->addMovement(_type);
    return true;
  }
  prepareToMove();
  switch (_direction)
  {
    case Indie::UP_DIRECTION:
      return (updateUp());
    case Indie::DOWN_DIRECTION:
      return (updateDown());
    case Indie::RIGHT_DIRECTION:
      return (updateRight());
    case Indie::LEFT_DIRECTION:
      return (updateLeft());
    case Indie::UNDEFINED_DIRECTION:
      return (true);
  }
  return true;
}

bool			StrafeEntity::updateUp()
{
//  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z + 0.4f})->getId() &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z + 0.4f})->crossEntity(_entity->getType(), true) &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z + 0.4f})->getPos().Y < _entity->getPos().Y)
//  {
//    _entity->addMovement(Indie::JUMP_UP_MOV);
//    return true;
//  }

  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z + 0.6f})->getId() &&
      !_entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z + 0.6f})->crossEntity(_entity->getType(), true))
    return (false);
  
  _entity->setPos({_entity->getPos().X,
		   _entity->getTile()->getPos().Y,
		   _entity->getPos().Z + 0.08f});
  return _entity->getPos().Z < _destTile->getPosCenter().Z;
}

bool			StrafeEntity::updateDown()
{
//  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z - 0.4f})->getId() &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z - 0.4f})->crossEntity(_entity->getType(), true) &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z - 0.4f})->getPos().Y < _entity->getPos().Y)
//  {
//    _entity->addMovement(Indie::JUMP_DOWN_MOV);
//    return true;
//  }

  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z - 0.6f})->getId() &&
      !_entity->getTile()->getMapHandler()->getTile({_entity->getPos().X, _entity->getPos().Y, _entity->getPos().Z - 0.6f})->crossEntity(_entity->getType(), true))
    return (false);

  _entity->setPos({_entity->getPos().X,
		   _entity->getTile()->getPos().Y,
		   _entity->getPos().Z - 0.08f});
  return _entity->getPos().Z > _destTile->getPosCenter().Z;
}

bool			StrafeEntity::updateLeft()
{
//  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X - 0.4f, _entity->getPos().Y, _entity->getPos().Z})->getId() &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X - 0.4f, _entity->getPos().Y, _entity->getPos().Z})->crossEntity(_entity->getType(), true) &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X - 0.4f, _entity->getPos().Y, _entity->getPos().Z})->getPos().Y < _entity->getPos().Y)
//  {
//    _entity->addMovement(Indie::JUMP_LEFT_MOV);
//    return true;
//  }

  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X - 0.6f, _entity->getPos().Y, _entity->getPos().Z})->getId() &&
      !_entity->getTile()->getMapHandler()->getTile({_entity->getPos().X - 0.6f, _entity->getPos().Y, _entity->getPos().Z})->crossEntity(_entity->getType(), true))
    return (false);

  _entity->setPos({_entity->getPos().X - 0.08f,
		   _entity->getTile()->getPos().Y,
		   _entity->getPos().Z});
  return _entity->getPos().X > _destTile->getPosCenter().X;
}

bool			StrafeEntity::updateRight()
{
//  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X + 0.4f, _entity->getPos().Y, _entity->getPos().Z})->getId() &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X + 0.4f, _entity->getPos().Y, _entity->getPos().Z})->crossEntity(_entity->getType(), true) &&
//      _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X + 0.4f, _entity->getPos().Y, _entity->getPos().Z})->getPos().Y < _entity->getPos().Y)
//  {
//    _entity->addMovement(Indie::JUMP_RIGHT_MOV);
//    return true;
//  }

  if (_entity->getTile()->getId() != _entity->getTile()->getMapHandler()->getTile({_entity->getPos().X + 0.6f, _entity->getPos().Y, _entity->getPos().Z})->getId() &&
      !_entity->getTile()->getMapHandler()->getTile({_entity->getPos().X + 0.6f, _entity->getPos().Y, _entity->getPos().Z})->crossEntity(_entity->getType(), true))
    return (false);

  _entity->setPos({_entity->getPos().X + 0.08f,
		   _entity->getTile()->getPos().Y,
		   _entity->getPos().Z});
  return _entity->getPos().X < _destTile->getPosCenter().X;
}

bool			StrafeEntity::update()
{
  switch (_direction)
  {
    case Indie::UP_DIRECTION:
      return (updateUp());
    case Indie::DOWN_DIRECTION:
      return (updateDown());
    case Indie::RIGHT_DIRECTION:
      return (updateRight());
    case Indie::LEFT_DIRECTION:
      return (updateLeft());
    case Indie::UNDEFINED_DIRECTION:
      return (true);
  }
  return true;
}