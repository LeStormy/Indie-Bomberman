/**
 * @Author: raph
 * @Date:   2017-06-14T17:39:26+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T22:23:04+02:00
 */
//
// Created by baptiste on 6/10/17.
//

#ifndef INDIESTUDIO_POWERKICKENTITY_HPP
#define INDIESTUDIO_POWERKICKENTITY_HPP

#include <memory>
#include "Core.hpp"
#include "Tile.hpp"
#include "AEntity.hpp"
#include "Indie.hpp"

class PowerEntity : public AEntity
{
  public:
    PowerEntity(Tile &tile, APlayer *)
    {
      _timer = 20;
      _tile = &tile;
      _tile->addAttractivity(40);
      _type = Indie::POWERKICK_ENTITY;
      init(Indie::POWERKICK_ENTITY, false);
      initParticlePower();
    }

    virtual ~PowerEntity()
    {
      _effects.clear();
      for (size_t i = 0; i < _ps.size(); i++)
      {
        _ps.at(i)->removeAllAffectors();
        _ps.at(i)->removeAnimators();
        _ps.at(i)->remove();
      }
      _node->remove();
    }

    void				update()
    {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->addEffect(Indie::KICK_EFFECT);
	  _tile->deleteEntities({Indie::POWERKICK_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::POWERKICK_ENTITY});
    }

  private:
    float 				_timer;
};

class InvincibleEntity : public AEntity
{
  public:
    InvincibleEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _timer = 20;
      _tile->addAttractivity(100);
      init(Indie::INVINCIBLE_ENTITY, false);
      initParticlePower();
    }

    virtual ~InvincibleEntity() {
      _effects.clear();
      for (size_t i = 0; i < _ps.size(); i++)
      {
        _ps.at(i)->removeAllAffectors();
        _ps.at(i)->removeAnimators();
        _ps.at(i)->remove();
      }
      _node->remove();
    }

    bool 	operator==(const Indie::Entity type) { return type == Indie::INVINCIBLE_ENTITY; }

    void update() {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->addEffect(Indie::INVINCIBLE_EFFECT);
	  _tile->deleteEntities({Indie::INVINCIBLE_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::INVINCIBLE_ENTITY});
    }

  private:
    float 				_timer;
};

class RangeUpEntity : public AEntity
{
  public:
    RangeUpEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _timer = 20;
      _tile->addAttractivity(40);
      init(Indie::RANGEUP_ENTITY, false);
      initParticlePower();
    }

    virtual ~RangeUpEntity() {
      _effects.clear();
      for (size_t i = 0; i < _ps.size(); i++)
      {
        _ps.at(i)->removeAllAffectors();
        _ps.at(i)->removeAnimators();
        _ps.at(i)->remove();
      }
      _node->remove();
    }

    bool 	operator==(const Indie::Entity type) { return type == Indie::RANGEUP_ENTITY; }

    void update() {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->incBombRange();
	  _tile->deleteEntities({Indie::RANGEUP_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::RANGEUP_ENTITY});
    }

  private:
    float 				_timer;
};


class RangeDownEntity : public AEntity
{
  public:
    RangeDownEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _timer = 20;
      _tile->addAttractivity(-40);
      init(Indie::RANGEDOWN_ENTITY, false);
      initParticlePower();
    }

  virtual ~RangeDownEntity() {
    _effects.clear();
    for (size_t i = 0; i < _ps.size(); i++)
    {
      _ps.at(i)->removeAllAffectors();
      _ps.at(i)->removeAnimators();
      _ps.at(i)->remove();
    }
    _node->remove();
  }

  bool 	operator==(const Indie::Entity type) { return type == Indie::RANGEDOWN_ENTITY; }

    void update() {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->decBombRange();
	  _tile->deleteEntities({Indie::RANGEDOWN_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::RANGEDOWN_ENTITY});
    }

  private:
    float 				_timer;
};

class BombUpEntity : public AEntity
{
  public:
    BombUpEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _timer = 20;
      _tile->addAttractivity(40);
      init(Indie::BOMBCUP_ENTITY, false);
      initParticlePower();
    }

  virtual ~BombUpEntity() {
    _effects.clear();
    for (size_t i = 0; i < _ps.size(); i++)
    {
      _ps.at(i)->removeAllAffectors();
      _ps.at(i)->removeAnimators();
      _ps.at(i)->remove();
    }
    _node->remove();
  }

  bool 	operator==(const Indie::Entity type) { return type == Indie::BOMBCUP_ENTITY; }

    void update() {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->incBombMax();
	  _tile->deleteEntities({Indie::BOMBCUP_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::BOMBCUP_ENTITY});
    }

  private:
    float 				_timer;
};

class BombDownEntity : public AEntity
{
  public:
    BombDownEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _timer = 20;
      _tile->addAttractivity(-40);
      init(Indie::BOMBDOWN_ENTITY, false);
      initParticlePower();
    }

  virtual ~BombDownEntity() {
    _effects.clear();
    for (size_t i = 0; i < _ps.size(); i++)
    {
      _ps.at(i)->removeAllAffectors();
      _ps.at(i)->removeAnimators();
      _ps.at(i)->remove();
    }
    _node->remove();
  }

    bool 	operator==(const Indie::Entity type) { return type == Indie::BOMBDOWN_ENTITY; }

    void update() {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->decBombMax();
	  _tile->deleteEntities({Indie::BOMBDOWN_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::BOMBDOWN_ENTITY});
    }

  private:
    float 				_timer;
};

class BombFreezerEntity : public AEntity
{
  public:
    BombFreezerEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _timer = 20;
      _tile->addAttractivity(10);
      init(Indie::BOMBFREEZER_ENTITY, false);
      initParticlePower();
    }

  virtual ~BombFreezerEntity() {
    _effects.clear();
    for (size_t i = 0; i < _ps.size(); i++)
    {
      _ps.at(i)->removeAllAffectors();
      _ps.at(i)->removeAnimators();
      _ps.at(i)->remove();
    }
    _node->remove();
  }

    bool 	operator==(const Indie::Entity type) { return type == Indie::BOMBFREEZER_ENTITY; }

    void update() {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->setBombType(Indie::FROZEN_BOMB);
	  _tile->deleteEntities({Indie::BOMBFREEZER_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::BOMBFREEZER_ENTITY});
    }

  private:
    float 				_timer;
};

class BombOilerEntity : public AEntity
{
  public:
    BombOilerEntity(Tile &tile, APlayer *)
    {
      _tile = &tile;
      _timer = 20;
      _tile->addAttractivity(10);
      init(Indie::BOMBOILER_ENTITY, false);
      initParticlePower();
    }

    virtual ~BombOilerEntity() {
      _effects.clear();
      for (size_t i = 0; i < _ps.size(); i++)
      {
        _ps.at(i)->removeAllAffectors();
        _ps.at(i)->removeAnimators();
        _ps.at(i)->remove();
      }
      _node->remove();
    }

    bool 	operator==(const Indie::Entity type) { return type == Indie::BOMBOILER_ENTITY; }

    void update() {
      for (auto & it : _tile->getPlayers())
	if (it != nullptr) {
	  Core::Sound.playSound(AUDIO("PowerUp"));
	  it->setBombType(Indie::OIL_BOMB);
	  _tile->deleteEntities({Indie::BOMBOILER_ENTITY});
	  return ;
	}
      if ((_timer -= Core::frameRate) <= 0)
	_tile->deleteEntities({Indie::BOMBOILER_ENTITY});
    }

  private:
    float 				_timer;
};

#endif //INDIESTUDIO_POWERKICKENTITY_HPP
