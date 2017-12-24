/**
 * @Author: raph
 * @Date:   2017-06-12T18:07:47+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T14:26:16+02:00
 */



//
// Created by baptiste on 6/5/17.
//

#ifndef INDIESTUDIO_STRAFEMOVEMENT_HPP
#define INDIESTUDIO_STRAFEMOVEMENT_HPP

#include "MovementManager.hpp"
#include "Core.hpp"

class StrafePlayer : public AMovement
{
  private:
    bool		updateUp();
    bool		updateDown();
    bool		updateLeft();
    bool		updateRight();
    void		rotate(Indie::Direction);

  public:
    StrafePlayer(APlayer *player, Indie::Direction direction)
    {
//      ISceneNodeAnimator* ani;

      switch (direction) {
	case Indie::UP_DIRECTION:
	  _type = Indie::STRAFE_UP_MOV;
	  break ;
	case Indie::DOWN_DIRECTION:
	  _type = Indie::STRAFE_DOWN_MOV;
	  break ;
	case Indie::LEFT_DIRECTION:
	  _type = Indie::STRAFE_LEFT_MOV;
	  break ;
	case Indie::RIGHT_DIRECTION:
	  _type = Indie::STRAFE_RIGHT_MOV;
	  break ;
	default:
	  break;
      }
      _player = player;
      _posReseted = false;
      _direction = direction;
      _player->animRunning();
      setPlayerDestTile();
    }
    virtual ~StrafePlayer()
    {
    };

    bool		update();

    bool		canBeChanged(Indie::Movement mov) {
      switch (mov) {
	case Indie::STRAFE_UP_MOV :
	  if (_direction == Indie::UP_DIRECTION)
	    return false;
	  break ;
	case Indie::STRAFE_DOWN_MOV :
	  if (_direction == Indie::DOWN_DIRECTION)
	    return false;
	  break ;
	case Indie::STRAFE_RIGHT_MOV :
	  if (_direction == Indie::RIGHT_DIRECTION)
	    return false;
	  break ;
	case Indie::STRAFE_LEFT_MOV :
	  if (_direction == Indie::LEFT_DIRECTION)
	    return false;
	  break ;
	default:
	  break;
      }
      return true;
    }
};

class StrafeEntity : public AMovement
{
  private:
    bool		updateUp();
    bool		updateDown();
    bool		updateLeft();
    bool		updateRight();

  public:
    StrafeEntity(AEntity *entity, Indie::Direction direction)
    {
  //    ISceneNodeAnimator* ani;

      _entity = entity;
      // _entity->addEffect();
      switch (direction) {
	case Indie::UP_DIRECTION:
	  _type = Indie::STRAFE_UP_MOV;
	  break ;
	case Indie::DOWN_DIRECTION:
	  _type = Indie::STRAFE_DOWN_MOV;
	  break ;
	case Indie::LEFT_DIRECTION:
	  _type = Indie::STRAFE_LEFT_MOV;
	  break ;
	case Indie::RIGHT_DIRECTION:
	  _type = Indie::STRAFE_RIGHT_MOV;
	  break ;
	default:
	  break;
      }
      _direction = direction;
      setEntityDestTile();
    }
    virtual ~StrafeEntity() { //_entity->removeEffect()
      };

    bool		update();

    bool		canBeChanged(Indie::Movement mov) {
      switch (mov) {
	case Indie::STRAFE_UP_MOV :
	  if (_direction == Indie::UP_DIRECTION)
	    return false;
	  break ;
	case Indie::STRAFE_DOWN_MOV :
	  if (_direction == Indie::DOWN_DIRECTION)
	    return false;
	  break ;
	case Indie::STRAFE_RIGHT_MOV :
	  if (_direction == Indie::RIGHT_DIRECTION)
	    return false;
	  break ;
	case Indie::STRAFE_LEFT_MOV :
	  if (_direction == Indie::LEFT_DIRECTION)
	    return false;
	  break ;
	default:
	  break;
      }
      return true;
    }
};

#endif //INDIESTUDIO_STRAFEMOVEMENT_HPP
