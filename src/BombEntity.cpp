/**
 * @Author: raph
 * @Date:   2017-06-07T13:37:18+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T22:41:54+02:00
 */



//
// Created by wurtz on 6/5/17.
//

#include "BombEntity.hpp"
#include "MapHandler.hpp"
#include "Tile.hpp"
#include "Core.hpp"

BombEntity::BombEntity(Tile &tile, APlayer *player)
{
  _timer = 2.0f;
  _tile = &tile;
  _tile->setTimeToDie(2.0f);
  _player = player;
  _range = _player->getBombRange();
  _type = Indie::BOMB_ENTITY;
  _mov.reset(new MovementManager(this));
  init(Indie::BOMB_ENTITY);
  _node->setAnimationSpeed(80);

  Tile *tmp = _tile;
  float timeToDie = (_tile->getTimeToDie() < (_timer -= Core::frameRate)
                     && _tile->getTimeToDie() != -1.0f) ? (_tile->getTimeToDie()) : (_timer);

  _tile->setTimeToDie(timeToDie);
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
                            (tmp = tmp->getMapHandler()->getTile<Indie::UP_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
                            (tmp = tmp->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
                            (tmp = tmp->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
                            (tmp = tmp->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }
  _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
  _effects.push_back(AEffect::createEffect(
      Indie::EffectType::CLASSICSMOKE_EFFECT,
      this, static_cast<uint16_t>(_ps.size() - 1),
      {{255, 163, 163, 163}, {255, 255, 255, 255}}));
  _tile->setTimeToDie(_timer);
}

BombEntity::~BombEntity() {
  Tile *tmp = _tile;

  _effects.clear();
  for (size_t i = 0; i < _ps.size(); i++)
  {
    _ps.at(i)->removeAllAffectors();
    _ps.at(i)->removeAnimators();
    _ps.at(i)->remove();
  }
  if (_tile->getValid()) {
    Core::Sound.playSound(AUDIO("Bomb"));

    for (uint16_t i = _range; i > 0 &&
                              (tmp = tmp->getMapHandler()->getTile<Indie::UP_DIRECTION>(
                                  tmp))
                              && tmp->getPos().Y == _tile->getPos().Y; --i) {
      if (tmp->isEntitiesExisting(
          {Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
        tmp->flameHit();
      else
        tmp->addEntity(Indie::FLAME_ENTITY, _player);
      if (!tmp->crossEntity(Indie::FLAME_ENTITY))
        break;
    }
    tmp = _tile;
    for (uint16_t i = _range; i > 0 &&
                              (tmp = tmp->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(
                                  tmp))
                              && tmp->getPos().Y == _tile->getPos().Y; --i) {
      if (tmp->isEntitiesExisting(
          {Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
        tmp->flameHit();
      else
        tmp->addEntity(Indie::FLAME_ENTITY, _player);
      if (!tmp->crossEntity(Indie::FLAME_ENTITY))
        break;
    }
    tmp = _tile;
    for (uint16_t i = _range; i > 0 &&
                              (tmp = tmp->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(
                                  tmp))
                              && tmp->getPos().Y == _tile->getPos().Y; --i) {

      if (tmp->isEntitiesExisting(
          {Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
        tmp->flameHit();
      else
        tmp->addEntity(Indie::FLAME_ENTITY, _player);
      if (!tmp->crossEntity(Indie::FLAME_ENTITY))
        break;
    }
    tmp = _tile;
    for (uint16_t i = _range; i > 0 &&
                              (tmp = tmp->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(
                                  tmp))
                              && tmp->getPos().Y == _tile->getPos().Y; --i) {
      if (tmp->isEntitiesExisting(
          {Indie::BREAKABLE_ENTITY, Indie::MAGNET_ENTITY}))
        tmp->flameHit();
      else
        tmp->addEntity(Indie::FLAME_ENTITY, _player);
      if (!tmp->crossEntity(Indie::FLAME_ENTITY))
        break;
    }
    _tile->addEntity(Indie::FLAME_ENTITY, _player);
    _tile->setReachable(true);
    _player->incBombCnt();
    _node->remove();
  }
}

void			BombEntity::update()
{
  Tile *tmp = _tile;

  _tile->setTimeToDie(_timer);
    float timeToDie = (_tile->getTimeToDie() < (_timer -= Core::frameRate)
		    && _tile->getTimeToDie() != -1.0f) ? (_tile->getTimeToDie()) : (_timer);

  _tile->setTimeToDie(timeToDie);
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
			    (tmp = tmp->getMapHandler()->getTile<Indie::UP_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
			    (tmp = tmp->getMapHandler()->getTile<Indie::DOWN_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
			    (tmp = tmp->getMapHandler()->getTile<Indie::RIGHT_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }
  tmp = _tile;
  for (uint16_t i = _range; i > 0 && tmp->getPos().Y == _tile->getPos().Y &&
			    (tmp = tmp->getMapHandler()->getTile<Indie::LEFT_DIRECTION>(tmp)); --i) {
    if (!tmp->crossEntity(Indie::FLAME_ENTITY))
      break;
    tmp->setTimeToDie(timeToDie);
  }

  for (uint16_t i = 0; i < _effects.size(); ++i)
    _effects[i]->update();

  if (std::all_of(_tile->getPlayers().begin(), _tile->getPlayers().end(), [] (APlayer *ply) { return ply == nullptr; }))
    _tile->setReachable(false);
  if (_timer <= 0)
    _tile->deleteEntities({Indie::BOMB_ENTITY});
  _mov->update();
}
