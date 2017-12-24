/**
 * @Author: raph
 * @Date:   2017-06-17T02:37:16+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:59:52+02:00
 */

//
// Created by yan on 25/05/17.
//

#include <random>
#include <cstring>
#include <ctime>
#include "Indie.hpp"
#include "ProceduralGeneration.hpp"

/*
 * Voir generateMap()
 */

ProceduralGeneration::ProceduralGeneration(MapSet & map)
        : _map(map),
          _height(_map.mapSize.second - 2),
          _width(_map.mapSize.first - 2),
          _platform(map.platforms)
{
    std::vector<Indie::Entity> entity;
    entity.push_back(Indie::Entity::GROUND_ENTITY);
    _map.newtiles = *new std::vector<std::vector<Indie::Entity>>();
    for (size_t cnt = 0; cnt < _map.mapSize.first * _map.mapSize.second; cnt++)
      _map.newtiles.push_back(entity);
    for (size_t cnt = 0; cnt < _map.mapSize.first * _map.mapSize.second; cnt++)
        _map.mapImage.map.push_back(1);
    _map.subBlockDensity.push_back(40);
    _map.subBlockDensity.push_back(60);
    _map.blockDensity = 100;
}

ProceduralGeneration::~ProceduralGeneration()
{

}

bool                    ProceduralGeneration::whatEntity(std::vector<Indie::Entity> tile, Indie::Entity type)
{
    for (Indie::Entity & ite : tile)
    {
        if (ite == type)
            return (true);
    }
    return (false);
}

bool                    ProceduralGeneration::setUnbreakable(size_t y, size_t x)
{
    std::vector<Indie::Entity>  & tile = this->getTile(y, x);

    if (!(whatEntity(tile, Indie::Entity::TRAMPOLINE_ENTITY))
        && !(whatEntity(tile, Indie::Entity::FORCEEMPTY_ENTITY)))
    {
      this->getTile(y, x).push_back(Indie::Entity::UNBREAKABLE_ENTITY);
      return (true);
    }
    else
      return (false);
}

void                    ProceduralGeneration::setItem(std::vector<Indie::Entity> & tile)
{
    for (int cnt = 0; cnt + 8 <= 9; cnt++)
    {
        if (std::rand() % 100 >= static_cast<int>(this->_map.subBlockDensity[cnt])
                && !(whatEntity(tile, Indie::UNBREAKABLE_ENTITY))
                && !(whatEntity(tile, Indie::BREAKABLE_ENTITY))
                   && !(whatEntity(tile, Indie::UNBREAKABLE_BORDER_ENTITY)))
        {
            if (whatEntity(tile, Indie::Entity::GROUND_ENTITY))
                tile.push_back(Indie::Entity::BREAKABLE_ENTITY);
            return;
        }
    }
}

void                                ProceduralGeneration::generateMap()
{
    std::vector<Indie::Entity>      tile;

    for (size_t iY = 0; iY < this->_map.mapSize.second ; iY++)
    {
        for (size_t iX = 0; iX < this->_map.mapSize.first ; iX++)
        {
            if (iX == 0  || iY == 0
                || iX == this->_map.mapSize.first - 1
                || iY == this->_map.mapSize.second - 1)
                this->getRealTile(iY , iX).push_back(Indie::Entity::UNBREAKABLE_BORDER_ENTITY);
        }
    }
    this->lockPlayerStart();
    this->generateUnbreakable();
    if (this->_platform)
        this->generatePlatform();
    for (size_t iY = 0; iY < this->_height; iY++)
    {
        for (size_t iX = 0; iX < this->_width; iX++)
        {
            tile = this->getTile(iY, iX);
            if (!(whatEntity(tile, Indie::Entity::TRAMPOLINE_ENTITY)))
            {
                if (std::rand() % 100 <= static_cast<int>(this->_map.blockDensity))
                    this->setItem(this->getTile(iY, iX));
            }
            if (whatEntity(tile, Indie::Entity::FORCEEMPTY_ENTITY))
            {
                tile.clear();
                tile.push_back(Indie::GROUND_ENTITY);
                this->getTile(iY, iX) = tile;
            }
        }
    }
}

std::vector<Indie::Entity> &               ProceduralGeneration::getTile(size_t y, size_t x)
{
    return (this->_map.newtiles[((x + 1) + ((y + 1) * this->_map.mapSize.first))]);
}

std::vector<Indie::Entity> &               ProceduralGeneration::getRealTile(size_t y, size_t x)
{
    return (this->_map.newtiles[x + (y * this->_map.mapSize.first)]);
}

void                    ProceduralGeneration::setLockEmpty(std::vector<Indie::Entity> &tile)
{
    if (!(whatEntity(tile, Indie::UNBREAKABLE_BORDER_ENTITY)))
    {
        tile.clear();
        tile.push_back(Indie::Entity::FORCEEMPTY_ENTITY);
    }
}

void                    ProceduralGeneration::lockPlayerStart()
{
    this->setLockEmpty(this->getTile(0, 0));
    this->setLockEmpty(this->getTile(0, 1));
    this->setLockEmpty(this->getTile(1, 0));

    this->setLockEmpty(this->getTile(this->_height - 1, 0));
    this->setLockEmpty(this->getTile(this->_height - 1, 1));
    this->setLockEmpty(this->getTile(this->_height - 2, 0));

    this->setLockEmpty(this->getTile(0, this->_width - 1));
    this->setLockEmpty(this->getTile(0, this->_width - 2));
    this->setLockEmpty(this->getTile(1, this->_width - 1));

    this->setLockEmpty(this->getTile(this->_height - 1, this->_width - 1));
    this->setLockEmpty(this->getTile(this->_height - 1, this->_width - 2));
    this->setLockEmpty(this->getTile(this->_height - 2, this->_width - 1));
}

bool                ProceduralGeneration::isHigh(size_t y, size_t x)
{
    if (this->_map.mapImage.getFloor((x + 1) + ((y + 1) * this->_map.mapSize.first)) == 1)
        return (true);
    return (false);
}

void          ProceduralGeneration::setTrampoNext(char platFormSide, size_t x, size_t y)
{
    if (platFormSide == 2)
    {
        this->setLockEmpty(this->getTile(y, x - 1));
        this->setLockEmpty(this->getTile(y, x + 1));
    }
    else if (platFormSide == 3)
    {
        this->setLockEmpty(this->getTile(y - 1, x));
        this->setLockEmpty(this->getTile(y + 1, x));
    }
}

void          ProceduralGeneration::setTrampo(size_t y, size_t x, size_t & cnt, char platFormSide)
{
    std::vector<Indie::Entity> &  tile = this->getTile(y, x);

    if (!(whatEntity(tile, Indie::Entity::TRAMPOLINE_ENTITY))
        && !(whatEntity(tile, Indie::Entity::FORCEEMPTY_ENTITY))
        && !(whatEntity(tile, Indie::Entity::UNBREAKABLE_ENTITY))
        && !(whatEntity(tile, Indie::Entity::UNBREAKABLE_BORDER_ENTITY)))
    {
        this->getTile(y, x).push_back(Indie::Entity::TRAMPOLINE_ENTITY);
        clearTrampo(y, x, platFormSide);
        if (platFormSide == 0)
        {
            this->setLockEmpty(this->getTile(y, x + 1));
            this->setLockEmpty(this->getTile(y, x - 1));
        }
        else if (platFormSide == 1)
        {
            this->setLockEmpty(this->getTile(y + 1, x));
            this->setLockEmpty(this->getTile(y - 1, x));
        }
        else
            setTrampoNext(platFormSide, x, y);
        cnt++;
    }
}
