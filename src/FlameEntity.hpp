//
// Created by baptiste on 6/4/17.
//

#ifndef INDIESTUDIO_FLAMEENTITY_HPP
#define INDIESTUDIO_FLAMEENTITY_HPP

#include "Indie.hpp"
#include "AEntity.hpp"

class FlameEntity : public AEntity
{
  private:
    float _timer;

  public:
    FlameEntity(Tile &tile, APlayer *player);
    virtual ~FlameEntity();

    bool operator==(const Indie::Entity type) { return type == Indie::FLAME_ENTITY; }

    void update();
};

#endif //INDIESTUDIO_FLAMEENTITY_HPP
