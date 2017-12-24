/**
 * @Author: raph
 * @Date:   2017-06-18T02:00:12+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T02:16:59+02:00
 */



//
// Created by wurtz on 17/05/17.
//

#include "AEntity.hpp"
#include "Core.hpp"
#include "MeshPathGetter.hpp"
#include "GrassEntity.hpp"
#include "BombEntity.hpp"
#include "BreakableEntity.hpp"
#include "SpikeEntity.hpp"
#include "FlameEntity.hpp"
#include "UnbreakableEntity.hpp"
#include "TrampolineEntity.hpp"
#include "PowerSpeedEntity.hpp"
#include "PowerEntity.hpp"
#include "MagnetEntity.hpp"
#include "FrozenBombEntity.hpp"
#include "IceEntity.hpp"
#include "OilBombEntity.hpp"
#include "FallEntity.hpp"

Indie::Biome                          AEntity::_biome = Indie::NEUTRAL;

void 				AEntity::setPos(const vector3df newPos)
{
  uint16_t newIndex = _tile->getMapHandler()->getIndex(newPos);

  _pos = newPos;
  _node->setPosition(newPos);
  if (newIndex != _tile->getId())
  {
    _tile->getMapHandler()->getTile(newIndex)->addEntity(shared_from_this());
    getTile()->deleteEntities({_type});
    if (foulOfPlayerMoves())
      getTile()->setReachable(true);
    _tile = _tile->getMapHandler()->getTile(newIndex);
  }
}

void 				AEntity::setForcePos(const vector3df newPos)
{
  _pos = newPos;
  _node->setPosition(newPos);
}

AEntity *AEntity::createEntity(Indie::Entity entity, Tile &tile, APlayer *player, Indie::Biome biome)
{
  _biome = biome;
  switch (entity)
  {
    case Indie::BOMB_ENTITY :
      return (new BombEntity(tile, player));
    case Indie::FROZENBOMB_ENTITY :
      return (new FrozenBombEntity(tile, player));
    case Indie::OILBOMB_ENTITY :
      return (new OilBombEntity(tile, player));
    case Indie::BREAKABLE_ENTITY :
      return (new BreakableEntity(tile, player));
    case Indie::UNBREAKABLE_BORDER_ENTITY :
      return (new UnbreakableEntity(tile, player, true));
    case Indie::UNBREAKABLE_ENTITY :
      return (new UnbreakableEntity(tile, player, false));
    case Indie::SPIKE_ENTITY :
      return (new SpikeEntity(tile, player));
    case Indie::TRAMPOLINE_ENTITY :
      return (new TrampolineEntity(tile, player));
    case Indie::GROUND_ENTITY :
      return (new GrassEntity(tile, player));
    case Indie::FLAME_ENTITY :
      return (new FlameEntity(tile, player));
    case Indie::POWERSPEED_ENTITY :
      return (new PowerSpeedEntity(tile, player));
    case Indie::POWERKICK_ENTITY :
      return (new PowerEntity(tile, player));
    case Indie::RANGEUP_ENTITY:
      return (new RangeUpEntity(tile, player));
    case Indie::RANGEDOWN_ENTITY:
      return (new RangeDownEntity(tile, player));
    case Indie::BOMBCUP_ENTITY:
      return (new BombUpEntity(tile, player));
    case Indie::BOMBDOWN_ENTITY:
      return (new BombDownEntity(tile, player));
    case Indie::BOMBFREEZER_ENTITY:
      return (new BombFreezerEntity(tile, player));
    case Indie::BOMBOILER_ENTITY:
      return (new BombOilerEntity(tile, player));
    case Indie::MAGNET_ENTITY :
      return (new MagnetEntity(tile, player));
    case Indie::ICE_ENTITY :
      return (new IceEntity(tile, player));
    case Indie::OIL_ENTITY :
      return (new OilEntity(tile, player));
    case Indie::INVINCIBLE_ENTITY :
      return (new InvincibleEntity(tile, player));
    case Indie::FALL_ENTITY :
      return (new FallEntity(tile, player));
    default:
      return nullptr;
  }
}

void AEntity::init(Indie::Entity entity, bool light, bool texture)
{
  _pos = _tile->getPosCenter();
  _node = Core::Display.smgr->addAnimatedMeshSceneNode(Core::Display.smgr->getMesh(MeshPathFromEnum::getMeshPath(entity, _biome, static_cast<int>(_pos.Y))));
  if (_node)
  {
    if (!light)
      _node->setMaterialFlag(EMF_LIGHTING, false);
    else
    {
      for (u32 i = _node->getMaterialCount(); i > 0; i--)
      {
        SMaterial &mat = _node->getMaterial(i);

        mat.Lighting=true;
        mat.NormalizeNormals=true;
        mat.AmbientColor=SColor(255,255,255,255);
        mat.DiffuseColor=SColor(255,255,255,255);
        mat.EmissiveColor=SColor(255,0,0,0);
        mat.SpecularColor=SColor(255,255,255,255);
      }
      _node->setMaterialFlag(video::EMF_LIGHTING, true);
      _node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
      _node->addShadowVolumeSceneNode();
    }
    if (texture) {
      _node->setMaterialTexture(0, Core::Display.driver->getTexture(MeshPathFromEnum::getTexturePath(entity, _biome, static_cast<int>(_pos.Y))));
    }
    _node->setPosition(_pos);
  }
}

void    AEntity::initParticlePower()
{
  _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
  _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
  _effects.push_back(AEffect::createEffect(
      Indie::EffectType::ROTATION_EFFECT,
      this, static_cast<uint16_t>(_ps.size() - 1),
      {{255, 163, 163, 163}, {255, 255, 255, 255}}));
}
