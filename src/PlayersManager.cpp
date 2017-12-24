/**
 * @Author: raph
 * @Date:   2017-06-07T13:37:18+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T03:10:20+02:00
 */
//
// Created by wurtz on 6/5/17.
//

#include "PlayersManager.hpp"
#include "APlayer.hpp"
#include "PlayerHuman.hpp"
#include "PlayerIA.hpp"

PlayersManager::PlayersManager(std::array<PlayerSet, 4> *players, MapHandler *mapHandler, Input *input)
{
  _playerSet = players;
  for (uint8_t i = 0; i < _players.size(); i++)
    switch (players->at(i).playerType)
    {
      case Indie::IA_PLAYER_EZ:
	_players.at(i) = std::make_unique<PlayerIA>(players->at(i), mapHandler, this, players->at(i).playerType);
	break ;
    case Indie::IA_PLAYER_MED:
    _players.at(i) = std::make_unique<PlayerIA>(players->at(i), mapHandler, this, players->at(i).playerType);
    break ;
    case Indie::IA_PLAYER_HARD:
    _players.at(i) = std::make_unique<PlayerIA>(players->at(i), mapHandler, this, players->at(i).playerType);
    break ;
      case Indie::HUMAN_PLAYER:
	_players.at(i) = std::make_unique<PlayerHuman>(players->at(i), mapHandler, input);
	break ;
      case Indie::UNUSED_PLAYER:
	_players.at(i) = nullptr;
	break ;
    }
};

bool				PlayersManager::isEnd()
{
  char alives = 0;
  for (size_t i = 0; i < 4; i++)
    if (_playerSet->at(i).playerType != Indie::UNUSED_PLAYER && _playerSet->at(i).alive)
      ++alives;
  if (alives > 1)
    return false;
  return true;
}

void				PlayersManager::update()
{
  if (isEnd())
  {
    for (auto &it : _players)
      if (it != nullptr && it->getAlive())
      {
	it->animCrazzy();
	it->setInvincible(true);
      }
  }
  for (auto & it : _players)
    if (it.get() != nullptr)
      it.get()->update();
}
