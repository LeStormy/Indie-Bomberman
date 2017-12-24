//
// Created by baptiste on 6/13/17.
//

#ifndef INDIESTUDIO_FROZENBOMBENTITY_HPP
#define INDIESTUDIO_FROZENBOMBENTITY_HPP


#include "AEntity.hpp"

class FrozenBombEntity : public AEntity
{
    float 	_timer;
    uint16_t 	_range;

  public:
    FrozenBombEntity(Tile &tile, APlayer *player);
    virtual ~FrozenBombEntity();

    virtual bool foulOfPlayerMoves() const { return true; }
    void update();
};

#endif //INDIESTUDIO_FROZENBOMBENTITY_HPP
