/**
 * @Author: raph
 * @Date:   2017-06-15T11:39:36+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:51:45+02:00
 */

//
// Created by wurtz on 17/05/17.
//

#include <algorithm>
#include "MapHandler.hpp"
#include "Tile.hpp"
#include "Core.hpp"

MapHandler::MapHandler(MapSet &mapSet, HUDSet *hudSet, std::array<PlayerSet, 4> *players)
{
  _playerSet = players;
  _hudSet = hudSet;
  _mapSize.first = mapSet.mapSize.first;
  _mapSize.second = mapSet.mapSize.second;
  for (uint16_t i = 0; i < mapSet.newtiles.size(); ++i)
    _tiles.push_back(std::make_shared<Tile>(&mapSet.newtiles[i], *this, i, mapSet.mapImage.getFloor(i), mapSet.Biome));
  //////
  _timerBonus = 0;
  /////
  _tileFall = getTile(0);
  _dirFall = Indie::RIGHT_DIRECTION;
  _posFall = {-1, 0, 0};
}

void				MapHandler::update()
{
  for (auto &it : _tiles)
    it->update();
  popRandBonus();
  popFallEntity();
}

template<>
Tile				*MapHandler::getTile<Indie::UP_DIRECTION>(Tile *tile)
{
  size_t			id;

  if ((id = tile->getId() + _mapSize.first) < _tiles.size())
    return _tiles[id].get();
  return nullptr;
}

template<>
Tile				*MapHandler::getTile<Indie::DOWN_DIRECTION>(Tile *tile)
{
  size_t			id;

  if ((id = tile->getId() - _mapSize.first) < _tiles.size())
    return _tiles[id].get();
  return nullptr;
}

template<>
Tile				*MapHandler::getTile<Indie::RIGHT_DIRECTION>(Tile *tile)
{
  size_t 			id;

  if ((id = tile->getId() + 1) < _tiles.size())
    return _tiles[id].get();
  return nullptr;
}

template<>
Tile				*MapHandler::getTile<Indie::LEFT_DIRECTION>(Tile *tile)
{
  size_t 			id;

  if ((id = tile->getId() - 1) < _tiles.size())
    return _tiles[id].get();
  return nullptr;
}

Tile				*MapHandler::getTile(vector3df pos)
{
  return _tiles.at(getIndex(pos)).get();
}

Tile				*MapHandler::getTile(uint16_t index)
{
  return _tiles.at(index).get();
}

const std::shared_ptr<Tile> & MapHandler::getTileIA(uint16_t index)
{
  return _tiles.at(index);
}

uint16_t			MapHandler::getIndex(const vector3df &pos) const
{
   uint16_t	  		index = static_cast<uint16_t>(pos.X) +
					static_cast<uint16_t>(pos.Z) *
					static_cast<uint16_t>(getWidth());

  if (index > _tiles.size() - 1)
    return (INT16_MAX);
  return index;
}

void				MapHandler::popRandBonus()
{
  uint16_t			rBonus;
  uint16_t			rTile;

    if (_hudSet->timer - _hudSet->elapsed.count() <= 35 &&
      (_timerBonus += Core::frameRate) > 0.5)
    {
      _timerBonus = 0;
      rBonus =  rand() % (Indie::ENTITY_COUNT - Indie::BONUS_ENTITY - 1) + Indie::BONUS_ENTITY + 1;
      rTile = static_cast<uint16_t>(rand() % (getWidth() * getHeight() - 1));
      if (rBonus != Indie::INVINCIBLE_ENTITY)
	getTile(rTile)->addEntity(static_cast<Indie::Entity>(rBonus), nullptr);
    }
}

void				MapHandler::popFallEntity()
{
  if (_hudSet->timer - _hudSet->elapsed.count() <= 25 &&
    (_timerFall += Core::frameRate) > 0.3 && !isEnd())
  {
    _timerFall = 0;
    switch (_dirFall)
    {
      case Indie::RIGHT_DIRECTION:
	if (_posFall.X == getWidth() - 1 - _posFall.Y)
	{
	  _dirFall = Indie::UP_DIRECTION;
	  ++_posFall.Z;
	}
	else
	  ++_posFall.X;
	break ;
      case Indie::UP_DIRECTION:
	if (_posFall.Z == getHeight() - 1 - _posFall.Y)
	{
	  _dirFall = Indie::LEFT_DIRECTION;
	  --_posFall.X;
	}
	else
	  ++_posFall.Z;
	break ;
      case Indie::LEFT_DIRECTION:
	if (_posFall.X == _posFall.Y)
	{
	  _dirFall = Indie::DOWN_DIRECTION;
	  --_posFall.Z;
	}
	else
	  --_posFall.X;
	break ;
      case Indie::DOWN_DIRECTION:
	if (_posFall.Z == _posFall.Y + 1)
	{
	  _dirFall = Indie::RIGHT_DIRECTION;
	  ++_posFall.X;
	  ++_posFall.Y;
	}
	else
	  --_posFall.Z;
	break ;
      default:
	break ;
    }
    getTile(_posFall)->addEntity(Indie::FALL_ENTITY, nullptr);
  }
}

bool				MapHandler::isEnd()
{
  char alives = 0;
  for (size_t i = 0; i < 4; i++)
    if (_playerSet->at(i).playerType != Indie::UNUSED_PLAYER && _playerSet->at(i).alive)
      ++alives;
  if (alives > 1)
    return false;
  return true;
}
