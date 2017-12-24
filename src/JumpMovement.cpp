/**
 * @Author: raph
 * @Date:   2017-06-15T11:39:36+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T14:21:41+02:00
 */

#include "JumpMovement.hpp"
#include "AEntity.hpp"

void			JumpPlayer::setPlayerDestTile()
{
  switch(_direction)
  {
    case Indie::UP_DIRECTION:
    {
      _destTile = _player->getMapHandler()->getTile<Indie::UP_DIRECTION>(_player->getTile());
      _angle.X = 3 * PI / 2;
      break;
    }
    case Indie::DOWN_DIRECTION:
    {
      _destTile = _player->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(_player->getTile());
      _angle.X = PI / 2;
      break;
    }
    case Indie::LEFT_DIRECTION:
    {
      _destTile = _player->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(_player->getTile());
      _angle.X = 0;
      break;
    }
    case Indie::RIGHT_DIRECTION:
    {
      _destTile = _player->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(_player->getTile());
      _angle.X = PI;
      break;
    }
    default :
      break ;
  }
  _posOrigin.X = (_player->getTile()->getPosCenter().X + _destTile->getPosCenter().X) / 2;
  _posOrigin.Z = (_player->getTile()->getPosCenter().Z + _destTile->getPosCenter().Z) / 2;

  _posOrigin.Y = _player->getTile()->getPos().Y;
  if (_destTile->getPos().Y < _posOrigin.Y)
    _posOrigin.Y = _destTile->getPos().Y;

  _size.Y = _player->getTile()->getPos().Y;
  if (_destTile->getPos().Y > _posOrigin.Y)
    _size.Y = _destTile->getPos().Y;

  _size.X = 0.5;
  _size.Y += 0.5;

  vector3df A = _posOrigin;
  vector3df B = _player->getPos();
  vector3df C;
  
  C.X = B.X;
  C.Z = B.Z;
  C.Y = A.Y;

  f32 p = (B.X-A.X)*(C.X-A.X) + (B.Y-A.Y)*(C.Y-A.Y) + (B.Z-A.Z)*(C.Z-A.Z);
  f32 nAB = sqrt( static_cast<f32>(pow((B.X-A.X), 2)) + static_cast<f32>(pow((B.Y-A.Y), 2)) + static_cast<f32>(pow((B.Z-A.Z), 2)) );
  f32 nAC = sqrt( static_cast<f32>(pow((C.X-A.X), 2)) + static_cast<f32>(pow((C.Y-A.Y), 2)) + static_cast<f32>(pow((C.Z-A.Z), 2)) );

  _angle.Y = cos(p/(nAB * nAC));
}

JumpPlayer::JumpPlayer(APlayer *player, Indie::Direction direction)
{
  _player = player;
  _direction = direction;
  _player->animJump();
  setPlayerDestTile();
}

bool		JumpPlayer::update()
{
  vector3df	pos;

  pos.X = _posOrigin.X + _size.X * cos(_angle.Y) * cos(_angle.X);
  pos.Z = _posOrigin.Z + _size.X * cos(_angle.Y) * sin(_angle.X);
  pos.Y = _posOrigin.Y + (_size.Y) * sin(_angle.Y);
  _angle.Y += 0.25f;
  if (_player->getPos().Y <= _destTile->getPos().Y && _angle.Y > PI / 2.0f)
  {
    _player->setPos({pos.X, _destTile->getPos().Y, pos.Z});
    return false;
  }
  _player->setPos(pos);
  return true;
}

void			JumpEntity::setEntityDestTile()
{
  switch(_direction)
  {
    case Indie::UP_DIRECTION:
    {
      _destTile = _entity->getTile()->getMapHandler()->getTile<Indie::UP_DIRECTION>(_entity->getTile());
      _angle.X = 3 * PI / 2;
      break;
    }
    case Indie::DOWN_DIRECTION:
    {
      _destTile = _entity->getTile()->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(_entity->getTile());
      _angle.X = PI / 2;
      break;
    }
    case Indie::LEFT_DIRECTION:
    {
      _destTile = _entity->getTile()->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(_entity->getTile());
      _angle.X = 0;
      break;
    }
    case Indie::RIGHT_DIRECTION:
    {
      _destTile = _entity->getTile()->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(_entity->getTile());
      _angle.X = PI;
      break;
    }
    default :
      break ;
  }
  _posOrigin.X = (_entity->getTile()->getPosCenter().X + _destTile->getPosCenter().X) / 2;
  _posOrigin.Z = (_entity->getTile()->getPosCenter().Z + _destTile->getPosCenter().Z) / 2;

  _posOrigin.Y = _entity->getTile()->getPos().Y;
  if (_destTile->getPos().Y < _posOrigin.Y)
    _posOrigin.Y = _destTile->getPos().Y;

  _size.Y = _entity->getTile()->getPos().Y;
  if (_destTile->getPos().Y > _posOrigin.Y)
    _size.Y = _destTile->getPos().Y;

  _size.X = 0.5;
  _size.Y += 0.5;

  vector3df A = _posOrigin;
  vector3df B = _entity->getPos();
  vector3df C;

  C.X = B.X;
  C.Z = B.Z;
  C.Y = A.Y;

  f32 p = (B.X-A.X)*(C.X-A.X) + (B.Y-A.Y)*(C.Y-A.Y) + (B.Z-A.Z)*(C.Z-A.Z);
  f32 nAB = sqrt( static_cast<f32>(pow((B.X-A.X), 2)) + static_cast<f32>(pow((B.Y-A.Y), 2)) + static_cast<f32>(pow((B.Z-A.Z), 2)) );
  f32 nAC = sqrt( static_cast<f32>(pow((C.X-A.X), 2)) + static_cast<f32>(pow((C.Y-A.Y), 2)) + static_cast<f32>(pow((C.Z-A.Z), 2)) );

  _angle.Y = cos(p/(nAB * nAC));
}

JumpEntity::JumpEntity(AEntity *entity, Indie::Direction direction)
{
  _entity = entity;
  _direction = direction;
  setEntityDestTile();
}

bool		JumpEntity::update()
{
  vector3df	pos;

  pos.X = _posOrigin.X + _size.X * cos(_angle.Y) * cos(_angle.X);
  pos.Z = _posOrigin.Z + _size.X * cos(_angle.Y) * sin(_angle.X);
  pos.Y = _posOrigin.Y + (_size.Y) * sin(_angle.Y);
  _angle.Y += 0.25f;
  if (_entity->getPos().Y <= _destTile->getPos().Y && _angle.Y > PI / 2.0f)
  {
    _entity->setPos({pos.X, _destTile->getPos().Y, pos.Z});
    return false;
  }
  _entity->setPos(pos);
  return true;
}
