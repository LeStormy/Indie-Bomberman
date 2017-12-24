//
// Created by wurtz on 6/18/17.
//

#ifndef INDIE_FALLENTITY_HPP
#define INDIE_FALLENTITY_HPP

#include "AEntity.hpp"

class FallEntity : public AEntity
{
  public:
    FallEntity(Tile &tile, APlayer *player);
    virtual ~FallEntity();

    bool 	operator==(const Indie::Entity type) { return type == Indie::FALL_ENTITY; }

    void update();
};

#endif //INDIE_FALLENTITY_HPP
