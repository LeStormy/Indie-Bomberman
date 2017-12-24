/**
 * @Author: raph
 * @Date:   2017-06-18T19:30:57+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T20:11:16+02:00
 */

#ifndef INDIE_FLAMEEFFECT_HPP
#define INDIE_FLAMEEFFECT_HPP

#include "AEffect.hpp"
#include "Core.hpp"
#include "AEntity.hpp"
#include "MeshPathGetter.hpp"

class FlameEffect : public AEffect
{
public:
  FlameEffect(Indie::EffectType bType, AEntity *entity, int id,
              std::pair<SColor, SColor> FlameColor =  {video::SColor(255, 235, 129, 33), video::SColor(255, 255, 236, 0)})
      : _loopTime(0.4f)
  {
    _timer = 0.8f;
    _actual_size = 0.15f;
    _baseHeight = 0.15f;
    _finalHeight = 0.7f;
    _id = id;
    _entity = entity;
    _particule = _entity->getParticuleSystem(
        id)->createAnimatedMeshSceneNodeEmitter(
        _entity->getNode(), false,
        core::vector3df(0.01f, 0.01f, 0.0f),
        100.0f, -1, false,
        80, 100,
        FlameColor.first,
        FlameColor.second,
        1000, 1500, 360,
        core::dimension2df(0.15f, 0.15f),
        core::dimension2df(0.15f, 0.15f));
    if (_particule) {
      _entity->getParticuleSystem(id)->setEmitter(_particule);
      scene::IParticleAffector *paf = entity->getParticuleSystem(
          id)->createFadeOutParticleAffector();
      _entity->getParticuleSystem(id)->addAffector(paf);
      _entity->getParticuleSystem(id)->setPosition(
          core::vector3df(_entity->getNode()->getPosition().X,
                          _entity->getNode()->getPosition().Y + 0.5f,
                          _entity->getNode()->getPosition().Z));
      _entity->getParticuleSystem(id)->setScale(
          core::vector3df(0.047f, 0.0065f, 0.1f));
      _entity->getParticuleSystem(id)->setMaterialFlag(video::EMF_LIGHTING,
                                                        false);
      _entity->getParticuleSystem(id)->setMaterialFlag(
          video::EMF_ZWRITE_ENABLE, false);
      _entity->getParticuleSystem(id)->setMaterialTexture(0,
                                                           Core::Display.driver->getTexture(
                                                               MeshPathFromEnum::getTexturePath(
                                                                   bType)));
      _entity->getParticuleSystem(id)->setMaterialType(
          video::EMT_TRANSPARENT_ADD_COLOR);
    }
  }

  ~FlameEffect()
  {
    if (_entity != nullptr)
    {
      _particule->drop();
      _entity->getParticuleSystem(_id)->clearParticles();
      _entity->getParticuleSystem(_id)->setEmitter(0);
    }
  };

  void update()
  {
    if (_entity)
    {
      _timer -= Core::frameRate;
      if (_timer < 0.7f)
        _particule->setDirection(core::vector3df(0.0001f, 0.0001f, 0.0f));
      if (_timer > 0.35f)
      {
        _actual_size += ((_finalHeight - _baseHeight) / (_loopTime / 2.0f)) * (Core::frameRate * 1.2f);
        _particule->setMinStartSize(dimension2d<f32>(_actual_size, _actual_size));
        _particule->setMaxStartSize(dimension2d<f32>(_actual_size, _actual_size));
      }
    }
  }

private:
  IParticleAnimatedMeshSceneNodeEmitter *_particule = nullptr;
  float   _actual_size;
  float   _baseHeight;
  float   _finalHeight;
  float   _loopTime;
};

#endif //INDIE_FLAMEEFFECT_HPP
