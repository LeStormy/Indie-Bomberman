//
// Created by wurtz on 6/4/17.
//

#ifndef INDIESTUDIO_BOMBENTITY_HPP
#define INDIESTUDIO_BOMBENTITY_HPP

#include "AEntity.hpp"

class BombEntity : public AEntity
{
  private:
    float 	_timer;
    uint16_t 	_range;

  public:
    BombEntity(Tile &tile, APlayer *player);
    virtual ~BombEntity();

    virtual bool                      foulOfPlayerMoves() const { return true; }
    void update();
};

#endif //INDIESTUDIO_BOMBENTITY_HPP
