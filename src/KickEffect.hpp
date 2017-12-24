//
// Created by baptiste on 6/10/17.
//

#ifndef INDIESTUDIO_KICKEFFECT_HPP
#define INDIESTUDIO_KICKEFFECT_HPP

#include "Core.hpp"

class KickEffect : public AEffect
{
  public:
    KickEffect(APlayer *ply, int id) {
      _type = Indie::KICK_EFFECT;
      _player = ply;
      _timer = 10;
      _id = id;
    }

    ~KickEffect() {}

    void update()
    {
      if ((_timer -= Core::frameRate) <= 0)
	_player->endOfEffect(_id);
    }
};

#endif //INDIESTUDIO_KICKEFFECT_HPP
