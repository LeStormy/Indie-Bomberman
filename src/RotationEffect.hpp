/**
 * @Author: raph
 * @Date:   2017-06-18T17:14:19+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T22:00:51+02:00
 */

#ifndef INDIE_ROTATIONEFFECT_HPP
#define INDIE_ROTATIONEFFECT_HPP

#include "AEffect.hpp"
#include "Core.hpp"
#include "AEntity.hpp"
#include "MeshPathGetter.hpp"

class RotationEffect : public AEffect
{
public:
  RotationEffect(Indie::EffectType bType, AEntity *entity, std::pair<SColor, SColor> rotationColor, int id)
  {
    _id = id;
    _entity = entity;
    IParticleAnimatedMeshSceneNodeEmitter	*particule;

    particule = entity->getParticuleSystem(id)->createAnimatedMeshSceneNodeEmitter(
        entity->getNode(), false,
        core::vector3df(0.0f, 0.0f, 0.0f),
        100.0f, -1, false,
        50, 80,
        rotationColor.first,
        rotationColor.second,
        100, 100, 30,
        core::dimension2df(0.1f, 0.1f),
        core::dimension2df(0.1f, 0.1f));
    entity->getParticuleSystem(id)->setEmitter(particule);
    particule->drop();

    scene::ISceneNodeAnimator *animrot =
        Core::Display.smgr->createFlyCircleAnimator(
            vector3df(entity->getNode()->getPosition().X,
                      entity->getNode()->getPosition().Y + 0.5f,
                      entity->getNode()->getPosition().Z), 0.7f, 0.001f,
            vector3df(1, 0, 0));
    entity->getParticuleSystem(id)->addAnimator(animrot);
    entity->getParticuleSystem(id)->setPosition(core::vector3df(entity->getNode()->getPosition().X,
                                                              entity->getNode()->getPosition().Y,
                                                              entity->getNode()->getPosition().Z));
    entity->getParticuleSystem(id)->setScale(core::vector3df(0.0047f, 0.0065f, 0.1f));
    entity->getParticuleSystem(id)->setMaterialFlag(video::EMF_LIGHTING, false);
    entity->getParticuleSystem(id)->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    entity->getParticuleSystem(id)->setMaterialTexture(0, Core::Display.driver->getTexture(
        MeshPathFromEnum::getTexturePath(bType)));
    entity->getParticuleSystem(id)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    entity->getParticuleSystem(id)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

    IParticleAnimatedMeshSceneNodeEmitter	*particule2;

    particule2 = entity->getParticuleSystem(id - 1)->createAnimatedMeshSceneNodeEmitter(
        entity->getNode(), false,
        core::vector3df(0.0f, 0.0f, 0.0f),
        100.0f, -1, false,
        50, 80,
        rotationColor.first,
        rotationColor.second,
        100, 100, 30,
        core::dimension2df(0.1f, 0.1f),
        core::dimension2df(0.1f, 0.1f));
    entity->getParticuleSystem(id - 1)->setEmitter(particule2);
    particule2->drop();

    scene::ISceneNodeAnimator *animrot2 =
        Core::Display.smgr->createFlyCircleAnimator(
            vector3df(entity->getNode()->getPosition().X,
                      entity->getNode()->getPosition().Y + 0.5f,
                      entity->getNode()->getPosition().Z), 0.7f, 0.001f,
            vector3df(0.0f, 1.0f, 0.0f));
    entity->getParticuleSystem(id - 1)->addAnimator(animrot2);
    entity->getParticuleSystem(id - 1)->setPosition(core::vector3df(entity->getNode()->getPosition().X,
                                                              entity->getNode()->getPosition().Y,
                                                              entity->getNode()->getPosition().Z));
    entity->getParticuleSystem(id - 1)->setScale(core::vector3df(0.0047f, 0.0065f, 0.1f));
    entity->getParticuleSystem(id - 1)->setMaterialFlag(video::EMF_LIGHTING, false);
    entity->getParticuleSystem(id - 1)->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    entity->getParticuleSystem(id - 1)->setMaterialTexture(0, Core::Display.driver->getTexture(
        MeshPathFromEnum::getTexturePath(bType)));
    entity->getParticuleSystem(id - 1)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    entity->getParticuleSystem(id - 1)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
  }

  ~RotationEffect()
  {
    _entity->getParticuleSystem(_id)->clearParticles();
    _entity->getParticuleSystem(_id)->setEmitter(0);
    _entity->getParticuleSystem(_id - 1)->clearParticles();
    _entity->getParticuleSystem(_id - 1)->setEmitter(0);
  };

  void update()
  {

  }
};

#endif //INDIE_ROTATIONEFFECT_HPP
