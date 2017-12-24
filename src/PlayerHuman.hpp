//
// Created by wurtz on 16/05/17.
//

#ifndef INDIESTUDIO_PLAYERHUMAIN_HPP
#define INDIESTUDIO_PLAYERHUMAIN_HPP

#include "Indie.hpp"
#include "APlayer.hpp"
#include "Settings.hpp"

class PlayerHuman : public APlayer
{
private:
  KeyMap			&_keyMap;
  Input				*_input;

public:
  PlayerHuman(PlayerSet &playerSet, MapHandler *map, Input *input);
  virtual ~PlayerHuman() {};

  void				update();
};

#endif //INDIESTUDIO_PLAYERHUMAIN_HPP
