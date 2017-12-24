/**
 * @Author: raph
 * @Date:   2017-06-16T18:27:40+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T20:01:36+02:00
 */

#ifndef INDIE_WINEFFECT_HPP
#define INDIE_WINEFFECT_HPP

#include "AEffect.hpp"
#include "Core.hpp"
#include "APlayer.hpp"
#include "MeshPathGetter.hpp"

class WinEffect : public AEffect
{
public:
  WinEffect(APlayer *entity, std::pair<SColor, SColor> playerColor, int id)
  {
    _id = id;
    _player = entity;
    IParticleAnimatedMeshSceneNodeEmitter	*particule;

    particule = entity->getParticuleSystem(_id)->createAnimatedMeshSceneNodeEmitter(
        entity->getNode(), false,
        core::vector3df(0.0f, 0.0f, 0.0f),
        100.0f, -1, false,
        500, 1000,
        playerColor.first,
        playerColor.second,
        500, 1000, 0,
        core::dimension2df(0.1f, 0.1f),
        core::dimension2df(0.3f, 0.3f));
    if (particule)
    {
      entity->getParticuleSystem(_id)->setEmitter(particule);
      particule->drop();

      scene::IParticleAffector *paf = entity->getParticuleSystem(_id)->createFadeOutParticleAffector();
      entity->getParticuleSystem(_id)->addAffector(paf);
      scene::ISceneNodeAnimator *animrot =
          Core::Display.smgr->createFlyCircleAnimator(
              vector3df(entity->getNode()->getPosition().X,
                        entity->getNode()->getPosition().Y + 1,
                        entity->getNode()->getPosition().Z), 1);
      entity->getParticuleSystem(_id)->addAnimator(animrot);
      entity->getParticuleSystem(_id)->setPosition(core::vector3df(entity->getNode()->getPosition().X,
                                                                entity->getNode()->getPosition().Y + 1,
                                                                entity->getNode()->getPosition().Z));
      entity->getParticuleSystem(_id)->setScale(core::vector3df(0.047f, 0.065f, 0.1f));
      entity->getParticuleSystem(_id)->setMaterialFlag(video::EMF_LIGHTING, false);
      entity->getParticuleSystem(_id)->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
      entity->getParticuleSystem(_id)->setMaterialTexture(0, Core::Display.driver->getTexture(
          MeshPathFromEnum::getTexturePath(Indie::EffectType::WIN_EFFECT)));
      entity->getParticuleSystem(_id)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    }
  }

  ~WinEffect()
  {
    _player->getParticuleSystem(_id)->clearParticles();
    _player->getParticuleSystem(_id)->setEmitter(0);
  };

  void update()
  {
    _player->getParticuleSystem(_id)->setPosition(vector3df(_player->getNode()->getPosition().X,
                                                         _player->getNode()->getPosition().Y + 1,
                                                         _player->getNode()->getPosition().Z));
  }
};

#endif //INDIE_WINEFFECT_HPP
