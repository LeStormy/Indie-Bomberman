

//
// Created by baptiste on 6/5/17.
//

#ifndef INDIESTUDIO_JUMPMOUVEMENT_HPP
#define INDIESTUDIO_JUMPMOUVEMENT_HPP


#include "MovementManager.hpp"
#include "Core.hpp"

class JumpPlayer : public AMovement
{
  private:
    vector3df		_posOrigin;
    vector2df		_angle;
    vector2df		_size;

  public:
    JumpPlayer(APlayer *player, Indie::Direction direction);
    virtual ~JumpPlayer()
    {
      _player->setAnim(false);
    }

    bool		update();

    void		setPlayerDestTile(); // tu la voulais pas en virtual plutôt ???? TODO
    bool		canBeChanged(Indie::Movement) { return false; }
};

class JumpEntity : public AMovement
{
  private:
    vector3df		_posOrigin;
    vector2df		_angle;
    vector2df		_size;

  public:
    JumpEntity(AEntity *entity, Indie::Direction direction);
    virtual ~JumpEntity() { }

    bool		update();

    void		setEntityDestTile();
    bool		canBeChanged(Indie::Movement) { return false; }
};

#endif //INDIESTUDIO_JUMPMOUVEMENT_HPP

