//
// Created by baptiste on 6/3/17.
//

#ifndef INDIESTUDIO_SPEEDBONUS_HPP
#define INDIESTUDIO_SPEEDBONUS_HPP

#include "AEffect.hpp"
#include "Core.hpp"
#include "APlayer.hpp"
#include "MeshPathGetter.hpp"

class SpeedUpEffect : public AEffect
{
public:
	SpeedUpEffect(APlayer *ply, int id)
	{
	  _id = id;
	  _player = ply;
	  _type = Indie::SPEED_EFFECT;
	  _player = ply;
	  _timer = 10;
	  if (_player->getRealSpeed() < 0.1f)
	    _player->setSpeed(_player->getRealSpeed() + 0.01f);
	}

	~SpeedUpEffect() {
		_player->setSpeed(_player->getRealSpeed() - 0.01f);
	}

	void update()
	{
	}
};

#endif //INDIESTUDIO_SPEEDBONUS_HPP
