//
// Created by wurtz on 6/4/17.
//

#ifndef INDIESTUDIO_SPIKEENTITY_HPP
#define INDIESTUDIO_SPIKEENTITY_HPP

#include "AEntity.hpp"

class SpikeEntity : public AEntity
{
  private:
    float			_timer;

  public:
    SpikeEntity(Tile &tile, APlayer *player);
    virtual ~SpikeEntity();

    bool 	operator==(const Indie::Entity type) { return type == Indie::SPIKE_ENTITY; }

    void update();
};

#endif //INDIESTUDIO_SPIKEENTITY_HPP
