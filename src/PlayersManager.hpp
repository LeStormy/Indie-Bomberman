/**
 * @Author: raph
 * @Date:   2017-06-07T13:37:18+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-13T18:27:19+02:00
 */

//
// Created by wurtz on 17/05/17.
//

#ifndef INDIESTUDIO_PLAYERMANAGER_HPP
#define INDIESTUDIO_PLAYERMANAGER_HPP

#include <memory>
#include "Settings.hpp"

class Tile;
class APlayer;
class MapHandler;

class PlayersManager
{
  private:
    std::array<std::unique_ptr<APlayer>, 4>	_players;
    std::array<PlayerSet, 4> 			*_playerSet;

    bool					isEnd();

  public:
    PlayersManager(std::array<PlayerSet, 4> *players, MapHandler *mapHandler, Input *input);
    ~PlayersManager() {};

    void					update();

    std::array<std::unique_ptr<APlayer>, 4> 	*getPlayers(void) { return &this->_players; }
};

#endif //INDIESTUDIO_PLAYERMANAGER_HPP
