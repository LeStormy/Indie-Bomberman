//
// Created by baptiste on 6/14/17.
//

#ifndef INDIESTUDIO_OILBOMBENTITY_HPP
#define INDIESTUDIO_OILBOMBENTITY_HPP

#include "AEntity.hpp"

class OilBombEntity : public AEntity
{
    float 	_timer;
    uint16_t 	_range;

  public:
    OilBombEntity(Tile &tile, APlayer *player);
    virtual ~OilBombEntity();

    virtual bool foulOfPlayerMoves() const { return true; }
    void update();
};

#endif //INDIESTUDIO_OILBOMBENTITY_HPP
