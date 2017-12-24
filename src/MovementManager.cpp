//
// Created by baptiste on 6/5/17.
//

#include "MovementManager.hpp"
#include "AEntity.hpp"
#include "MapHandler.hpp"
#include "JumpMovement.hpp"
#include "StrafeMovement.hpp"
#include "APlayer.hpp"
#include "Tile.hpp"

void			AMovement::setPlayerDestTile()
{
  switch(_direction)
  {
    case Indie::UP_DIRECTION:
    {
      if (_player->getPos().Z < _player->getTile()->getPosCenter().Z)
	_destTile = _player->getTile();
      else
	_destTile = _player->getMapHandler()->getTile<Indie::UP_DIRECTION>(_player->getTile());
      break ;
    }
    case Indie::DOWN_DIRECTION:
    {
      if (_player->getPos().Z > _player->getTile()->getPosCenter().Z)
	_destTile = _player->getTile();
      else
	_destTile = _player->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(_player->getTile());
      break ;
    }
    case Indie::LEFT_DIRECTION:
    {
      if (_player->getPos().X > _player->getTile()->getPosCenter().X)
	_destTile = _player->getTile();
      else
	_destTile = _player->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(_player->getTile());
      break ;
    }
    case Indie::RIGHT_DIRECTION:
    {
      if (_player->getPos().X < _player->getTile()->getPosCenter().X)
	_destTile = _player->getTile();
      else
	_destTile = _player->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(_player->getTile());
      break ;
    }
    case Indie::UNDEFINED_DIRECTION:
      break ;
  }
}

void			AMovement::setEntityDestTile()
{
  Tile 			*tmp = _entity->getTile();
  Tile 			*tmp2 = tmp;

  switch(_direction)
  {
    case Indie::UP_DIRECTION:
      while ((tmp = _entity->getTile()->getMapHandler()->getTile<Indie::UP_DIRECTION>(tmp)) != nullptr
		&& tmp->checkAddEntity(Indie::BOMB_ENTITY) && tmp->getPos().Y <= tmp2->getPos().Y)
	tmp2 = tmp;
      _destTile = tmp2;
      break ;
    case Indie::DOWN_DIRECTION:
      while ((tmp = _entity->getTile()->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(tmp)) != nullptr
	     && tmp->checkAddEntity(Indie::BOMB_ENTITY) && tmp->getPos().Y <= tmp2->getPos().Y)
	tmp2 = tmp;
      _destTile = tmp2;
      break ;
    case Indie::LEFT_DIRECTION:
      while ((tmp = _entity->getTile()->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(tmp)) != nullptr
	     && tmp->checkAddEntity(Indie::BOMB_ENTITY) && tmp->getPos().Y <= tmp2->getPos().Y)
	tmp2 = tmp;
      _destTile = tmp2;
      break ;
    case Indie::RIGHT_DIRECTION:
      while ((tmp = _entity->getTile()->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(tmp)) != nullptr
	     && tmp->checkAddEntity(Indie::BOMB_ENTITY) && tmp->getPos().Y <= tmp2->getPos().Y)
	tmp2 = tmp;
      _destTile = tmp2;
      break ;
    case Indie::UNDEFINED_DIRECTION:
      break ;
  }
}

void			AMovement::centerPlayerPos()
{
  _player->setPos(_player->getTile()->getPosCenter());
  _posReseted = true;
}

void			AMovement::prepareToMove()
{
  if (!_posReseted)
  {
    switch (_direction) {
      case Indie::UP_DIRECTION:
	if (_player->getPos().Z != _player->getTile()->getPosCenter().Z)
	  centerPlayerPos();
	break ;
      case Indie::DOWN_DIRECTION:
	if (_player->getPos().Z != _player->getTile()->getPosCenter().Z)
	  centerPlayerPos();
	break ;
      case Indie::LEFT_DIRECTION:
	if (_player->getPos().X != _player->getTile()->getPosCenter().X)
	  centerPlayerPos();
	break ;
      case Indie::RIGHT_DIRECTION:
	if (_player->getPos().X != _player->getTile()->getPosCenter().X)
	  centerPlayerPos();
	break ;
      case Indie::UNDEFINED_DIRECTION:
	break ;
    }
    _posReseted = true;
  }
}

/**
**********************
**/

void			MovementManager::addMovement(Indie::Movement move)
{
  if (_move != nullptr ? !_move->canBeChanged(move) : false)
    return ;
  switch (move)
  {
    case Indie::STRAFE_UP_MOV:
      if (_player)
	_move.reset(new StrafePlayer(_player, Indie::UP_DIRECTION));
      else
	_move.reset(new StrafeEntity(_entity, Indie::UP_DIRECTION));
      break ;
    case Indie::STRAFE_DOWN_MOV:
      if (_player)
	_move.reset(new StrafePlayer(_player, Indie::DOWN_DIRECTION));
      else
	_move.reset(new StrafeEntity(_entity, Indie::DOWN_DIRECTION));
      break ;
    case Indie::STRAFE_LEFT_MOV:
      if (_player)
	_move.reset(new StrafePlayer(_player, Indie::LEFT_DIRECTION));
      else
	_move.reset(new StrafeEntity(_entity, Indie::LEFT_DIRECTION));
      break ;
    case Indie::STRAFE_RIGHT_MOV:
      if (_player)
	_move.reset(new StrafePlayer(_player, Indie::RIGHT_DIRECTION));
      else
	_move.reset(new StrafeEntity(_entity, Indie::RIGHT_DIRECTION));
      break ;

    case Indie::JUMP_UP_MOV:
      if (_player)
	_move.reset(new JumpPlayer(_player, Indie::UP_DIRECTION));
      else
	_move.reset(new JumpEntity(_entity, Indie::UP_DIRECTION));
      break ;
    case Indie::JUMP_DOWN_MOV:
      if (_player)
	_move.reset(new JumpPlayer(_player, Indie::DOWN_DIRECTION));
      else
	_move.reset(new JumpEntity(_entity, Indie::DOWN_DIRECTION));
      break ;
    case Indie::JUMP_LEFT_MOV:
      if (_player)
	_move.reset(new JumpPlayer(_player, Indie::LEFT_DIRECTION));
      else
	_move.reset(new JumpEntity(_entity, Indie::LEFT_DIRECTION));
      break ;
    case Indie::JUMP_RIGHT_MOV:
      if (_player)
	_move.reset(new JumpPlayer(_player, Indie::RIGHT_DIRECTION));
      else
	_move.reset(new JumpEntity(_entity, Indie::RIGHT_DIRECTION));
      break ;
  }
  _move->update();
}

void			MovementManager::update()
{
  if (_move != nullptr)
    if (!_move->update())
      _move.reset(nullptr);
}

Indie::Direction	MovementManager::getDirection() const
{
  if (_move)
    return _move->getDirection();
  return Indie::UNDEFINED_DIRECTION;
}