/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-29T13:22:00+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-05-29T13:25:24+02:00
 */
//
// Created by baptiste on 5/12/17.
//

#ifndef MAP_HANDLER_HPP
#define MAP_HANDLER_HPP

#include <memory>
#include <vector>
#include "Settings.hpp"

class Tile;

class MapHandler
{
  private:
    std::pair<size_t, size_t>			_mapSize;
    std::vector<std::shared_ptr<Tile>>		_tiles;
    HUDSet					*_hudSet;
    std::array<PlayerSet, 4> 			*_playerSet;
    float					_timerBonus;
    Indie::Direction				_dirFall;
    Tile					*_tileFall;
    float					_timerFall;
    vector3df					_posFall;

    void					popRandBonus();
    void					popFallEntity();
    bool					isEnd();

  public:
    MapHandler(MapSet &mapSet, HUDSet *hudSet, std::array<PlayerSet, 4> *players);
    ~MapHandler() {}

    void					update();

    inline size_t				getWidth() const { return _mapSize.first; }
    inline size_t				getHeight() const { return _mapSize.second; }
    uint16_t					getIndex(const vector3df &pos) const;
    inline std::vector<std::shared_ptr<Tile>>	*getTiles() { return &_tiles; }
    template<Indie::Direction T>
    Tile					*getTile(Tile *tile);
    Tile					*getTile(vector3df pos);
    Tile					*getTile(uint16_t index);
    const std::shared_ptr<Tile> 		&getTileIA(uint16_t index);
};

#endif /* !MAP_HANDLER_HPP */
