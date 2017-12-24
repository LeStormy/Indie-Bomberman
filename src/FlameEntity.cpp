/**
 * @Author: raph
 * @Date:   2017-06-15T11:39:36+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T14:22:53+02:00
 */

#include "FlameEntity.hpp"
#include "Core.hpp"

FlameEntity::FlameEntity(Tile &tile, APlayer *player)
{
  _timer = 0.8f;
  _tile = &tile;
  _player = player;
  _tile->setTimeToDie(0.0f);
  init(Indie::FLAME_ENTITY, false);
  _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
  _effects.push_back(AEffect::createEffect(
      Indie::EffectType::FLAME_EFFECT,
      this, static_cast<uint16_t>(_ps.size() - 1)));
}

FlameEntity::~FlameEntity()
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

void FlameEntity::update()
{
  std::for_each(_tile->getPlayers().begin(), _tile->getPlayers().end(), [] (APlayer *ply) { ply ? ply->killMe() : (void)ply; });

  _tile->setTimeToDie(0.0f);
  if (_timer <= 0.9)
    _tile->deleteEntities(_tile->getDeleteEntityRule(Indie::FLAME_ENTITY));
  if ((_timer -= Core::frameRate) <= 0)
    _tile->deleteEntities({Indie::FLAME_ENTITY});
  for (uint16_t i = 0; i < _effects.size(); ++i)
    _effects[i]->update();
}
