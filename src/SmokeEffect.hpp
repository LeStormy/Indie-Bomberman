/**
 * @Author: raph
 * @Date:   2017-06-18T17:14:19+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T20:01:15+02:00
 */

#ifndef INDIE_SMOKEEFFECT_HPP
#define INDIE_SMOKEEFFECT_HPP

#include "AEffect.hpp"
#include "Core.hpp"
#include "AEntity.hpp"
#include "MeshPathGetter.hpp"

class SmokeEffect : public AEffect
{
public:
  SmokeEffect(Indie::EffectType bType, AEntity *entity, std::pair<SColor, SColor> smokeColor, int id)
  {
    _id = id;
    _entity = entity;
    IParticleAnimatedMeshSceneNodeEmitter	*particule;

    particule = _entity->getParticuleSystem(id)->createAnimatedMeshSceneNodeEmitter(
        _entity->getNode(), false,
        core::vector3df(0.0f, 0.001f, 0.0f),
        100.0f, -1, false,
        1000, 2000,
        smokeColor.first,
        smokeColor.second,
        100, 1000, 30,
        core::dimension2df(0.2f, 0.2f),
        core::dimension2df(0.2f, 0.2f));
    if (particule)
    {
      _entity->getParticuleSystem(id)->setEmitter(particule);
      particule->drop();

      scene::IParticleAffector *paf = entity->getParticuleSystem(id)->createFadeOutParticleAffector();
      _entity->getParticuleSystem(id)->addAffector(paf);
      _entity->getParticuleSystem(id)->setPosition(core::vector3df(_entity->getNode()->getPosition().X,
                                                                _entity->getNode()->getPosition().Y + 1,
                                                                _entity->getNode()->getPosition().Z));
      _entity->getParticuleSystem(id)->setScale(core::vector3df(0.0047f, 0.0065f, 0.1f));
      _entity->getParticuleSystem(id)->setMaterialFlag(video::EMF_LIGHTING, false);
      _entity->getParticuleSystem(id)->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
      _entity->getParticuleSystem(id)->setMaterialTexture(0, Core::Display.driver->getTexture(
          MeshPathFromEnum::getTexturePath(bType)));
      _entity->getParticuleSystem(id)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    }
  }

  SmokeEffect(Indie::EffectType bType, APlayer *player, std::pair<SColor, SColor> smokeColor, int id)
  {
    _id = id;
    _player = player;
    IParticleAnimatedMeshSceneNodeEmitter	*particule;

    particule = _player->getParticuleSystem(id)->createAnimatedMeshSceneNodeEmitter(
        _player->getNode(), false,
        core::vector3df(0.0f, 0.001f, 0.0f),
        100.0f, -1, false,
        1000, 2000,
        smokeColor.first,
        smokeColor.second,
        100, 1000, 30,
        core::dimension2df(0.2f, 0.2f),
        core::dimension2df(0.2f, 0.2f));
    if (particule)
    {
      _player->getParticuleSystem(id)->setEmitter(particule);
      particule->drop();

      scene::IParticleAffector *paf = _player->getParticuleSystem(id)->createFadeOutParticleAffector();
      _player->getParticuleSystem(id)->addAffector(paf);
      _player->getParticuleSystem(id)->setPosition(core::vector3df(_player->getNode()->getPosition().X,
                                                                   _player->getNode()->getPosition().Y,
                                                                   _player->getNode()->getPosition().Z));
      _player->getParticuleSystem(id)->setScale(core::vector3df(0.0047f, 0.0065f, 0.1f));
      _player->getParticuleSystem(id)->setMaterialFlag(video::EMF_LIGHTING, false);
      _player->getParticuleSystem(id)->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
      _player->getParticuleSystem(id)->setMaterialTexture(0, Core::Display.driver->getTexture(
          MeshPathFromEnum::getTexturePath(bType)));
      _player->getParticuleSystem(id)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    }
  }


  ~SmokeEffect()
  {
    if (_entity != nullptr)
    {
      _entity->getParticuleSystem(_id)->clearParticles();
      _entity->getParticuleSystem(_id)->setEmitter(0);
    }
    if (_player != nullptr)
    {
      _player->getParticuleSystem(_id)->clearParticles();
      _player->getParticuleSystem(_id)->setEmitter(0);
    }
  };

  void update()
  {
    if (_entity)
      _entity->getParticuleSystem(_id)->setPosition(vector3df(_entity->getNode()->getPosition().X,
                                                               _entity->getNode()->getPosition().Y + 1,
                                                               _entity->getNode()->getPosition().Z));
    if (_player)
      _player->getParticuleSystem(_id)->setPosition(vector3df(_player->getNode()->getPosition().X,
                                                              _player->getNode()->getPosition().Y,
                                                              _player->getNode()->getPosition().Z));
  }
};
#endif //INDIE_SMOKEEFFECT_HPP
