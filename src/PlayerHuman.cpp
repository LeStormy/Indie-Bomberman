/**
 * @Author: raph
 * @Date:   2017-06-13T23:06:46+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T17:13:59+02:00
 */



//
// Created by baptiste on 5/23/17.
//

#include "Indie.hpp"
#include "PlayerHuman.hpp"
#include "MapHandler.hpp"
#include "Core.hpp"

PlayerHuman::PlayerHuman(PlayerSet &playerSet, MapHandler *mapHandler, Input *input)
  : _keyMap(playerSet.keyMap)
{
  _sets = &playerSet;
  _mapHandler = mapHandler;
  _input = input;
  _bombType = Indie::CLASSIC_BOMB;
  init();
  animIdle();
}

void				PlayerHuman::update()
{
  bool animMove = false;

  if (_sets->alive)
  {
    std::array<bool, 5>		playerActions = _input->getPlayerAction(_sets->id);

    if (playerActions[Indie::BOMB_ACTION_PLAYER])
      dropBomb();
    for (uint8_t i = 0; i < playerActions.size() - 1; ++i)
      if (playerActions[i])
      {
	move(static_cast<Indie::ActionPlayer>(i));
	animMove = true;
      }
    if (!animMove)
      animIdle();
    _mov->update();
    for (uint16_t i = 0; i < _effects.size(); ++i)
      _effects[i]->update();
  }
}
