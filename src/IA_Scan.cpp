/**
 * @Author: raph
 * @Date:   2017-06-18T17:14:19+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T20:22:52+02:00
 */
//
// Created by daine on 6/13/17.
//

#include "PlayerIA.hpp"
#include "Core.hpp"

float        PlayerIA::isTileSafe(std::shared_ptr<scanTile> tile)
{
    if (tile->_tile->getTimeToDie() == _noDanger
        || tile->_eta + _reactivityLag < tile->_tile->getTimeToDie()
            || tile->_eta > tile->_tile->getTimeToDie() + _reactivityLag + _safeZone)
        return (_noDanger);
    return (tile->_tile->getTimeToDie() + _safeZone);
}

void        PlayerIA::setPath(scanTile *start)
{
    std::shared_ptr<scanTile>             actual;
    std::deque<std::shared_ptr<scanTile>> _tmpPath;
    float                                 dangerLevel;

    _currentPath.clear();
    actual = std::make_shared<scanTile>();
    actual->_tile = start->_tile;
    actual->_parent = start->_parent;
    actual->_eta = start->_eta;
    while (actual->_tile->getPosCenter().Z != _sets->position.Z
           || actual->_tile->getPosCenter().X != _sets->position.X)
    {
        _tmpPath.push_front(actual);
        actual = actual->_parent;
        if (actual->_tile->getPos().Z == actual->_parent->_tile->getPos().Z
            && actual->_tile->getPos().X == actual->_parent->_tile->getPos().X)
            break ;
    }
    for (auto &it : _tmpPath)
    {
        if ((dangerLevel = isTileSafe(it)) != _noDanger)
        {
            if (_currentPath.size() == 0)
            {
                _currentAction = Action::WAIT;
                _wait = dangerLevel;
            }
            return ;
        }
        _currentPath.push_back(it->_tile);
    }
}

int                    PlayerIA::isPlayerNearBy()
{
    float                 dist;
    int                 bestDist = 100;

    for (int idx = 0 ; idx < 4 ; idx++)
    {
        if (playersManager->getPlayers()->at(idx) != nullptr && playersManager->getPlayers()->at(idx)->getAlive() && getId() != idx)
        {
            dist = (abs(_mapHandler->getTileIA(playersManager->getPlayers()->at(idx)->getTile()->getId())->getPos().Z - _mapHandler->getTileIA(_idTile)->getPos().Z)
                    > abs(_mapHandler->getTileIA(playersManager->getPlayers()->at(idx)->getTile()->getId())->getPos().X - _mapHandler->getTileIA(_idTile)->getPos().X))
                   ? abs(_mapHandler->getTileIA(playersManager->getPlayers()->at(idx)->getTile()->getId())->getPos().Z - _mapHandler->getTileIA(_idTile)->getPos().Z)
                   : abs(_mapHandler->getTileIA(playersManager->getPlayers()->at(idx)->getTile()->getId())->getPos().X - _mapHandler->getTileIA(_idTile)->getPos().X);
            if (dist < bestDist)
                bestDist = static_cast<int>(dist);
        }
    }
    return (bestDist);
}


int             PlayerIA::getDist(std::shared_ptr<Tile> src, std::shared_ptr<Tile> dest)
{
    return (static_cast<int>((abs(src->getPos().X - dest->getPos().X)
             + (abs(src->getPos().Z - dest->getPos().Z)))));
}

bool            PlayerIA::findInterest(std::shared_ptr<Tile> nearByPlayer, scanTile *&best)
{
    if (nearByPlayer == nullptr)
        return (false);
    for (auto & it : _scanedTile)
    {
        if (nearByPlayer->getPos().X == it->_tile->getPos().X
            && nearByPlayer->getPos().Z == it->_tile->getPos().Z)
        {
            best = it.get();
            return (true);
        }
        else
        {
            if (best != nullptr)
            {
                if (getDist(it->_tile, nearByPlayer) < getDist(best->_tile, nearByPlayer))
                    best = it.get();
            }
            else
                best = it.get();
        }
    }
    return (false);
}

std::shared_ptr<Tile>   PlayerIA::getNearbyPlayer()
{
    int                 bestDist = 100;
    int                 dist;
    std::shared_ptr<Tile> ret;

    for (int idx = 0 ; idx < 4 ; idx++)
    {
        if (playersManager->getPlayers()->at(idx) != nullptr
            && playersManager->getPlayers()->at(idx)->getAlive()
            && getId() != idx)
        {
            dist = getDist(_mapHandler->getTileIA(playersManager->getPlayers()->at(idx)->getTile()->getId()),
                           _mapHandler->getTileIA(getTile()->getId()));
            if (dist < bestDist)
            {
                bestDist = dist;
                ret = _mapHandler->getTileIA(playersManager->getPlayers()->at(idx)->getTile()->getId());
            }
        }
    }
    return (ret);
}

bool        PlayerIA::findInterest(Tile *self, scanTile *& best)
{
    for (auto & it : _scanedTile)
    {
        if (it->_tile->getTimeToDie() == _noDanger
            && it->_tile->getPos().X != self->getPos().X
                && it->_tile->getPos().Z != self->getPos().Z)
        {
            best = it.get();
            return (true);
        }
    }
    return (false);
}

bool        PlayerIA::findInterest(scanTile *& best, float)
{
    best = _scanedTile[0].get();
    for (auto & it : _scanedTile)
    {
        if (it->_tile->getTimeToDie() == _noDanger)
        {
            best = it.get();
            return (true);
        }
        else if (it->_tile->getTimeToDie() > best->_tile->getTimeToDie())
            best = it.get();
    }
    return (false);
}

bool        PlayerIA::findInterest(scanTile *&best)
{
    int         x;
    int         z;

    for (auto it = _scanedTile.rbegin(); it != _scanedTile.rend(); ++it)
    {
        if (it->get()->_tile->isEntitiesExisting(_powerupInterest))
        {
            best = it->get();
            return (true);
        }
        else
        {
            x = static_cast<int>(it->get()->_tile->getPos().X);
            z = static_cast<int>(it->get()->_tile->getPos().Z);
            if ((x - 1 > 0
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x - 1 + z * _mapHandler->getWidth()))->isEntitiesExisting(_breakable))
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x - 1 + z * _mapHandler->getWidth()))->getPos().Y <= it->get()->_tile->getPos().Y))
                || ((x + 1 < static_cast<int>(_mapHandler->getWidth()))
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x + 1 + z * _mapHandler->getWidth()))->isEntitiesExisting(_breakable))
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x + 1 + z * _mapHandler->getWidth()))->getPos().Y <= it->get()->_tile->getPos().Y))
                || (z - 1 > 0
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x + (z - 1) * _mapHandler->getWidth()))->isEntitiesExisting(_breakable))
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x + (z - 1) * _mapHandler->getWidth()))->getPos().Y <= it->get()->_tile->getPos().Y))
                || ((z + 1 < static_cast<int>(_mapHandler->getHeight()))
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x + (z + 1) * _mapHandler->getWidth()))->isEntitiesExisting(_breakable))
                    && (_mapHandler->getTileIA(static_cast<uint16_t>(x + (z + 1) * _mapHandler->getWidth()))->getPos().Y <= it->get()->_tile->getPos().Y)))
                best = it->get();
        }
    }
    return (false);
}

float        PlayerIA::calculateEta(std::shared_ptr<scanTile> &tile)
{
    float     x;
    float     z;

    x = abs(tile->_tile->getPos().X - tile->_parent->_tile->getPos().X);
    z = abs(tile->_tile->getPos().Z - tile->_parent->_tile->getPos().Z);
    if (tile->_parent->_tile->getPos().Y > 0)
        return ((((x + z) * Core::frameRate) / _sets->speed) + tile->_parent->_eta + 1.0f);
    return ((((x + z) * Core::frameRate) / _sets->speed) + tile->_parent->_eta);
}

void        PlayerIA::addTile(std::shared_ptr<Tile> &newTile, std::shared_ptr<scanTile> parent, float eta)
{
    size_t  elem = _scanedTile.size();

    this->_scanedTile.push_back(std::make_shared<scanTile>());
    this->_scanedTile[elem]->_tile = newTile;
    this->_scanedTile[elem]->_parent = parent;
    this->_scanedTile[elem]->_eta = eta;
}

bool        PlayerIA::checkTile(std::shared_ptr<scanTile> tile, float x, float z)
{
    std::shared_ptr<Tile> currentTile;
    bool      find = false;
    float     eta;

    currentTile = _mapHandler->getTileIA(static_cast<uint16_t>(x + z * _mapHandler->getWidth()));
    eta = calculateEta(tile);
    if (isTileValid(currentTile, tile))
    {
        addTile(currentTile, tile, eta);
        find = true;
    }
    return (find);
}

bool        PlayerIA::scan()
{
    size_t  startSize = _scanedTile.size();
    float     x;
    float     z;
    bool      find = false;
    std::shared_ptr<Tile> parentTile;
    std::shared_ptr<Tile> currentTile;

    for (size_t i = _startScan; i < startSize; i++)
    {
        parentTile = _scanedTile[i]->_tile;
        x = parentTile->getPos().X;
        z = parentTile->getPos().Z;
        if (x - 1 > 0 && checkTile(_scanedTile[i], x - 1, z))
                find = true;
        if (x + 1 < _mapHandler->getWidth() && checkTile(_scanedTile[i], x + 1, z))
                find = true;
        if (z - 1 > 0 && checkTile(_scanedTile[i], x, z - 1))
                find = true;
        if (z + 1 < _mapHandler->getHeight() && checkTile(_scanedTile[i], x, z + 1))
                find = true;
        ++_startScan;
    }
    return (find);
}

bool        PlayerIA::isTileValid(std::shared_ptr<Tile> &tile, std::shared_ptr<scanTile> &parent)
{
    if (tile->getReachable() == false)
        return (false);
    else if (tile->getPos().Y > parent->_tile->getPos().Y
             && !(parent->_tile->isEntitiesOnTile(Indie::Entity::TRAMPOLINE_ENTITY)))
        return (false);
    else if (tile.get()->getPos().Z == parent->_parent->_tile->getPos().Z
             && tile.get()->getPos().X == parent->_parent->_tile->getPos().X)
        return (false);
    return (true);
}

void            PlayerIA::initScan()
{
    _startScan = 0;
    _scanedTile.clear();
    _scanedTile.push_back(std::make_shared<scanTile>());
    _scanedTile[0]->_tile = _mapHandler->getTileIA(_idTile);
    _scanedTile[0]->_parent = _scanedTile[0];
    _scanedTile[0]->_eta = 0.0;
}
