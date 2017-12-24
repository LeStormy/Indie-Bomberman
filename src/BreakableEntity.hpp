/**
 * @Author: raph
 * @Date:   2017-06-15T16:53:34+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T16:53:45+02:00
 */



//
// Created by wurtz on 6/4/17.
//

#ifndef INDIESTUDIO_BREAKABLEENTITY_HPP
#define INDIESTUDIO_BREAKABLEENTITY_HPP

#include "AEntity.hpp"
#include "Tile.hpp"

class BreakableEntity : public AEntity
{
  private:
    Indie::Entity 	getRandedBonus() const {
      int 		rand = std::rand() % 100;
      if (rand < 20)
        return (Indie::POWERSPEED_ENTITY);
      if (rand < 30)
        return (Indie::POWERKICK_ENTITY);
      if (rand < 40)
        return (Indie::BOMBDOWN_ENTITY);
      if (rand < 50)
        return (Indie::BOMBCUP_ENTITY);
      if (rand < 60)
        return (Indie::RANGEUP_ENTITY);
      if (rand < 70)
        return (Indie::RANGEDOWN_ENTITY);
      if (rand < 80)
        return (Indie::BOMBFREEZER_ENTITY);
      if (rand < 90)
        return (Indie::BOMBOILER_ENTITY);
      return (Indie::INVINCIBLE_ENTITY);
    }
  public:
    BreakableEntity(Tile &tile, APlayer *player) : _flameHit(false)
    {
      _tile = &tile;
      _player = player;
      _tile->setReachable(false);
      init(Indie::BREAKABLE_ENTITY);
    }

  virtual ~BreakableEntity()
  {
    _effects.clear();
    for (size_t i = 0; i < _ps.size(); i++)
    {
      _ps.at(i)->removeAllAffectors();
      _ps.at(i)->removeAnimators();
      _ps.at(i)->remove();
    }
    _node->remove();
    _tile->setTimeToDie(-1.0f);
  }

  bool 		operator==(const Indie::Entity type) { return type == Indie::BREAKABLE_ENTITY; }

  virtual void	onFlameHit()
  {
    if (_flameHit == true)
      return ;
    _flameHit = true;
    _tile->setReachable(true);
    _node->setMaterialTexture(0, Core::Display.driver->getTexture(MeshPathFromEnum::getTexturePath(Indie::CLASSICSMOKE_EFFECT)));
    _node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    if (std::rand() % 10 < 8)
      _tile->addEntity(getRandedBonus(), nullptr);
    _timer = 1.0;
    _tile->setTimeToDie(0.0f);
    _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
    _effects.push_back(AEffect::createEffect(
        Indie::EffectType::FLAME_EFFECT,
        this, static_cast<uint16_t>(_ps.size() - 1),
        {{255, 163, 163, 163}, {255, 255, 255, 255}}));
  }

  void 		update()
  {
    if (_flameHit)
    {
      _tile->setTimeToDie(_timer);
      for (uint16_t i = 0; i < _effects.size(); ++i)
        _effects[i]->update();
      std::for_each(_tile->getPlayers().begin(), _tile->getPlayers().end(),
                    [] (APlayer *ply)
                    { ply ? ply->killMe() : (void)ply; } );
      if ((_timer -= Core::frameRate) <= 0)
        _tile->deleteEntities({Indie::BREAKABLE_ENTITY});
    }
  }

private:
  bool 		_flameHit;
  float 		_timer;
};

#endif //INDIESTUDIO_BREAKABLEENTITY_HPP
