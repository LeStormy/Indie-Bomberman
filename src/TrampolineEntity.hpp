//
// Created by wurtz on 6/4/17.
//

#ifndef INDIESTUDIO_TRAMPOLINEENTITY_HPP
#define INDIESTUDIO_TRAMPOLINEENTITY_HPP

#include "AEntity.hpp"
#include "Tile.hpp"
#include "MapHandler.hpp"
#include "APlayer.hpp"

class TrampolineEntity : public AEntity
{
  public:
    TrampolineEntity(Tile &tile, APlayer *player);
    virtual ~TrampolineEntity();

    void		update();
};


#endif //INDIESTUDIO_TRAMPOLINEENTITY_HPP
