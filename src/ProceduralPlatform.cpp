/**
 * @Author: raph
 * @Date:   2017-06-17T21:46:55+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-17T21:47:49+02:00
 */

//
// Created by yan on 25/05/17.
//

#include "ProceduralGeneration.hpp"

void                ProceduralGeneration::horizontalPlatForm()
{
    size_t          newW;
    size_t          newH;
    size_t          newX;
    size_t          newY;
    size_t          nbAccess;

    newX = 0;
    if (this->_height - 6 <= 3)
    {
        this->midPlatForm();
        return ;
    }
    else
        newY = std::rand() % (this->_height - 6) + 2;
    newH = (this->_height / 3);
    newW = newH - 1;
    nbAccess = newW;
    if (nbAccess >= 3)
        nbAccess = 3;
    this->setPlatform(newY, newX, newW, newH, nbAccess);
    newX = this->_width - newW;
    if (this->_height - 6 <= 3)
    {
        this->midPlatForm();
        return ;
    }
    else
        newY = std::rand() % (this->_height - 6) + 2;
    this->setPlatform(newY, newX, newW, newH, nbAccess);
}

void                ProceduralGeneration::verticalPlatForm()
{
    size_t          newW;
    size_t          newH;
    size_t          newX;
    size_t          newY;
    size_t          nbAccess;

    if (this->_width - 6 <= 3)
    {
        this->midPlatForm();
        return ;
    }
    else
    {
        newX = std::rand() % (this->_width - 6) + 2;
    }
    newY = 0;
    newH = (this->_width / 3);
    newW = newH - 1;
    nbAccess = newW;
    if (nbAccess >= 3)
        nbAccess = 3;
    this->setPlatform(newY, newX, newW, newH, nbAccess);
    if (this->_width - 6 <= 3)
    {
        this->midPlatForm();
        return ;
    }
    else
    {
        newX = std::rand() % (this->_width - 6) + 2;
    }
    newY = this->_height - newH;
    this->setPlatform(newY, newX, newW, newH, nbAccess);
}

void                ProceduralGeneration::midPlatForm()
{
    size_t          newW;
    size_t          newH;
    size_t          newX;
    size_t          newY;
    size_t          nbAccess;

    if (this->_width >= this->_height)
    {
        newW = this->_width / 3;
        newH = newW - 1;
        newX = (this->_width / 2) - (newW / 2);
        newY = (this->_height / 2) - (newH / 2);
        nbAccess = newW;
    }
    else
    {
        newH = this->_height / 3;
        newW = newH - 1;
        newX = (this->_width / 2) - ((this->_width / 3) / 2);
        newY = (this->_height / 2) - ((this->_width / 3) ) / 2;
        nbAccess = newW;
    }
    if (nbAccess >= 4)
        nbAccess = 4;
    this->setPlatform(newY, newX, newW, newH, nbAccess);
}

bool                ProceduralGeneration::checkWay(size_t y, size_t x, char platformside)
{
  if (((platformside == 0 || platformside == 2)
        && !(whatEntity(this->getTile(y, x + 1),
                        Indie::Entity::UNBREAKABLE_ENTITY))
         && !(whatEntity(this->getTile(y, x + 1),
                           Indie::Entity::UNBREAKABLE_BORDER_ENTITY))
        && !(whatEntity(this->getTile(y, x - 1),
                        Indie::Entity::UNBREAKABLE_ENTITY))
        && !(whatEntity(this->getTile(y, x - 1),
                        Indie::Entity::UNBREAKABLE_BORDER_ENTITY)))
        || ((platformside == 1 || platformside == 3)
            && !(whatEntity(this->getTile(y + 1, x),
                            Indie::Entity::UNBREAKABLE_ENTITY))
            && !(whatEntity(this->getTile(y + 1, x),
                               Indie::Entity::UNBREAKABLE_BORDER_ENTITY))
            && !(whatEntity(this->getTile(y - 1, x),
                                  Indie::Entity::UNBREAKABLE_BORDER_ENTITY))
            && !(whatEntity(this->getTile(y - 1, x),
                            Indie::Entity::UNBREAKABLE_ENTITY))))
        return (true);
    return (false);
}

bool                ProceduralGeneration::clearTrampo(size_t y, size_t x, char platformside)
{
    int             tmpY = y;
    int             tmpX = x;

    std::vector<Indie::Entity>         tile;

    if (std::rand() % 2 == 0)
    {
        if (std::rand() % 2 == 0)
            --tmpY;
        else
            ++tmpY;
    }
    else
    {
        if (std::rand() % 2 == 0)
            --tmpX;
        else
            ++tmpX;
    }
    tile = this->getTile(tmpY, tmpX);
    if (!(whatEntity(tile, Indie::Entity::UNBREAKABLE_ENTITY))
        && !(whatEntity(tile, Indie::Entity::TRAMPOLINE_ENTITY))
           && !(whatEntity(tile, Indie::Entity::UNBREAKABLE_BORDER_ENTITY))
        && !(this->isHigh(tmpY, tmpX)))
    {
        if (checkWay(y, x, platformside))
        {
            this->setLockEmpty(this->getTile(tmpY, tmpX));
            return (true);
        }
        return (false);
    }
    else if ((whatEntity(tile, Indie::Entity::FORCEEMPTY_ENTITY)))
        return (true);
    return (false);
}

void                ProceduralGeneration::setHeight(size_t y, size_t x)
{
    std::vector<Indie::Entity> &       tile = this->getTile(y, x);

    if (!(isHigh(y, x)))
    {
        this->_map.mapImage.map[(x + 1) + (y + 1) * this->_map.mapSize.first] = tile[0] << 8; //TODO
        this->_map.mapImage.map[(x + 1) + (y + 1) * this->_map.mapSize.first] += 1;
    }
}

void                ProceduralGeneration::setPlatformNext(size_t y, size_t x, size_t w, size_t h, size_t rand, size_t & i)
{
    if (rand == 2 && (x + w) < this->_width)
        this->setTrampo((std::rand() % h) + y, x + w, i, 2);
    else if (rand == 3 && (y + h) < this->_height)
        this->setTrampo(y + h, (std::rand() % w) + x, i, 3);
}

void                ProceduralGeneration::setPlatform(size_t y, size_t x, size_t w, size_t h, size_t nbAccess)
{
    size_t          i = 0;
    size_t          rand;

    for(size_t iY = 0; iY < h; iY++)
    {
        for (size_t iX = 0; iX < w; iX++)
            setHeight(y + iY, x + iX);
    }
    while (i < nbAccess)
    {
        rand = std::rand() % 4;
        if (rand == 0 && x > 0)
            this->setTrampo((std::rand() % h) + y, x - 1, i, 0);
        else if (rand == 1 && y > 0)
            this->setTrampo(y - 1, (std::rand() % w) + x, i, 1);
        else
            this->setPlatformNext(y, x, w, h, rand, i);
    }
}

void                ProceduralGeneration::generatePlatform()
{
    size_t          rand;

    rand = std::rand() % 2;
    if (rand == 0)
        this->verticalPlatForm();
    else if (rand == 1)
        this->horizontalPlatForm();
    else
        this->midPlatForm();
}
