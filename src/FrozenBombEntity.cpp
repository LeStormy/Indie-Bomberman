//
// Created by baptiste on 6/13/17.
//

#include "FrozenBombEntity.hpp"
#include "MapHandler.hpp"
#include "Tile.hpp"
#include "Core.hpp"
#include "APlayer.hpp"

FrozenBombEntity::FrozenBombEntity(Tile &tile, APlayer *player)
{
  _timer = 2.0;
  _tile = &tile;
  _player = player;
  _range = _player->getBombRange();
  _type = Indie::FROZENBOMB_ENTITY;
  _mov.reset(new MovementManager(this));
  init(Indie::FROZENBOMB_ENTITY);
  _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
  _effects.push_back(AEffect::createEffect(
      Indie::EffectType::FROZENSMOKE_EFFECT,
      this, static_cast<uint16_t>(_ps.size() - 1),
      {{255, 148, 255, 255}, {255, 125, 251, 255}}));
}

FrozenBombEntity::~FrozenBombEntity()
{
  Tile *tmp = _tile;

  _effects.clear();
  for (size_t i = 0; i < _ps.size(); i++)
  {
    _ps.at(i)->removeAllAffectors();
    _ps.at(i)->removeAnimators();
    _ps.at(i)->remove();
  }
  Core::Sound.playSound(AUDIO("BombIce"));
  for (uint16_t i = _range; i > 0 && (tmp = tmp->getMapHandler()->getTile<Indie::UP_DIRECTION>(tmp))
			    && tmp->getPos().Y == _tile->getPos().Y; --i) {
    if (!tmp->isEntitiesExisting({Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
      tmp->addEntity(Indie::ICE_ENTITY, _player);
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break ;
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && (tmp = tmp->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(tmp))
			    && tmp->getPos().Y == _tile->getPos().Y; --i) {
    if (!tmp->isEntitiesExisting({Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
      tmp->addEntity(Indie::ICE_ENTITY, _player);
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break ;
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && (tmp = tmp->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(tmp))
			    && tmp->getPos().Y == _tile->getPos().Y; --i) {

    if (!tmp->isEntitiesExisting({Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
      tmp->addEntity(Indie::ICE_ENTITY, _player);
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break ;
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && (tmp = tmp->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(tmp))
			    && tmp->getPos().Y == _tile->getPos().Y; --i) {
    if (!tmp->isEntitiesExisting({Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
      tmp->addEntity(Indie::ICE_ENTITY, _player);
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break ;
  }
  _tile->addEntity(Indie::ICE_ENTITY, _player);
  _tile->setReachable(true);
  _player->incBombCnt();
  _node->remove();

}

void			FrozenBombEntity::update()
{
  if (std::all_of(_tile->getPlayers().begin(), _tile->getPlayers().end(), [] (APlayer *ply) { return ply == nullptr; }))
    _tile->setReachable(false);
  if ((_timer -= Core::frameRate) <= 0)
    _tile->deleteEntities({Indie::FROZENBOMB_ENTITY});
  for (uint16_t i = 0; i < _effects.size(); ++i)
    _effects[i]->update();
  _mov->update();
}
