//
// Created by baptiste on 6/13/17.
//

#ifndef INDIESTUDIO_POWERUPSEFFECTS_HPP
#define INDIESTUDIO_POWERUPSEFFECTS_HPP

#include "Core.hpp"

class InvincibleEffect : public AEffect
{
  public:
    InvincibleEffect(APlayer *ply, int id) {
      _type = Indie::INVINCIBLE_EFFECT;
      _player = ply;
      _timer = 5;
      _id = id;
    }

    virtual ~InvincibleEffect() {}

    void update()
    {
      if ((_timer -= Core::frameRate) <= 0)
	_player->endOfEffect(_id);
    }
};

class OilEffect : public AEffect
{
  public:
    OilEffect(APlayer *ply, int id) {
      _type = Indie::OIL_EFFECT;
      _player = ply;
      _id = id;
      _player->setSpeed(_player->getRealSpeed() + 0.02f);
    }

    virtual ~OilEffect() { _player->setSpeed(_player->getRealSpeed() - 0.02f); }

    void update()
    {
	_player->endOfEffect(_id);
    }
};

class IceEffect : public AEffect
{
  public:
    IceEffect(APlayer *ply, int id) {
      _type = Indie::ICE_EFFECT;
      _id = id;
      _player = ply;
      _player->setSpeed(_player->getRealSpeed() - 0.02f);
    }
    virtual ~IceEffect() { _player->setSpeed(_player->getRealSpeed() + 0.02f); }

    void update()
    {
      _player->endOfEffect(_id);
    }
};

#endif //INDIESTUDIO_POWERUPSEFFECTS_HPP
