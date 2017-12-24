/**
 * @Author: raph
 * @Date:   2017-06-14T16:07:49+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T05:37:30+02:00
 */



//
// Created by wurtz on 17/05/17.
//

#include "APlayer.hpp"
#include "Core.hpp"
#include "MeshPathGetter.hpp"
#include "MovementManager.hpp"
#include "AEffect.hpp"

void 				APlayer::init()
{
  _mov.reset(new MovementManager(this));
  _idTile = getMapHandler()->getIndex(_sets->position);
  _direction = Indie::DOWN_DIRECTION;
  _node = Core::Display.smgr->addAnimatedMeshSceneNode(Core::Display.smgr->getMesh(MeshPathFromEnum::getMeshPath(Indie::HUMAN_PLAYER, Indie::SNOWY, _sets->id)));
  getMapHandler()->getTile(_idTile)->setPlayer(this, _sets->id);
  if (_node)
  {
    _node->addShadowVolumeSceneNode();
    _node->setMD2Animation(scene::EMAT_STAND);
    _node->setMaterialTexture(0, Core::Display.driver->getTexture(MeshPathFromEnum::getTexturePath(Indie::HUMAN_PLAYER, Indie::SNOWY, _sets->id)));
    _node->setPosition(_sets->position);
    _node->setRotation({0, 0, 0});
  }
}

void				APlayer::move(Indie::ActionPlayer playerAction)
{
  switch (playerAction)
  {
    case Indie::UP_ACTION_PLAYER:
      _direction = Indie::UP_DIRECTION;
      _mov->addMovement(Indie::STRAFE_UP_MOV);
      break ;
    case Indie::DOWN_ACTION_PLAYER:
      _direction = Indie::DOWN_DIRECTION;
      _mov->addMovement(Indie::STRAFE_DOWN_MOV);
      break ;
    case Indie::LEFT_ACTION_PLAYER:
      _direction = Indie::LEFT_DIRECTION;
      _mov->addMovement(Indie::STRAFE_LEFT_MOV);
      break ;
    case Indie::RIGHT_ACTION_PLAYER:
      _direction = Indie::RIGHT_DIRECTION;
      _mov->addMovement(Indie::STRAFE_RIGHT_MOV);
      break ;
    default:
      break ;
  }
}

void				APlayer::dropBomb()
{
  if (getBombUp()) {
    switch (_bombType)
    {
      case Indie::FROZEN_BOMB:
	if (getTile()->addEntity(Indie::FROZENBOMB_ENTITY, this))
	  decBombCnt();
	_bombType = Indie::CLASSIC_BOMB;
	break ;
      case Indie::OIL_BOMB:
	if (getTile()->addEntity(Indie::OILBOMB_ENTITY, this))
	  decBombCnt();
	_bombType = Indie::CLASSIC_BOMB;
	break ;
      case Indie::CLASSIC_BOMB:
	if (getTile()->addEntity(Indie::BOMB_ENTITY, this))
	  decBombCnt();
	break ;
    }
  }
}

void 				APlayer::killMe(bool force)
{
  if ((_sets->alive && !hasBonus(Indie::INVINCIBLE_EFFECT)) ||
    (force && !_invicible))
  {
    _effects.clear();
    _mov.reset(nullptr);
    if (!_ps.empty())
    {
      for (size_t i = 0; i < _ps.size(); i++)
      {
        _ps.at(i)->removeAllAffectors();
        _ps.at(i)->removeAnimators();
        _ps.at(i)->remove();
      }
      _ps.clear();
    }
    getTile()->setPlayer(nullptr, getId());
    _node->remove();
    _sets->alive = false;
  }
}

void				APlayer::setPos(const vector3df newPos)
{
  uint16_t newIndex = getMapHandler()->getIndex(newPos);

  _sets->position = newPos;
  _node->setPosition(newPos);
  if (newIndex != _idTile)
  {
    getTile()->setPlayer(nullptr, _sets->id);
    _idTile = newIndex;
    getMapHandler()->getTile(_idTile)->setPlayer(this, _sets->id);
  }
}

Tile				*APlayer::getTile() const
{
  return getMapHandler()->getTile(_idTile);
}

void        APlayer::victoryEffect(std::pair<SColor, SColor> playerColor)
{
  _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
  _effects.push_back(AEffect::createEffect(Indie::WIN_EFFECT,
                                           this,
                                           static_cast<uint16_t>(_ps.size() - 1),
                                           playerColor));
}

void 			APlayer::setInvincible(const bool state)
{
  _invicible = state;
}

void 				APlayer::addEffect(Indie::EffectType effect)
{
  if (effect == Indie::EffectType::INVINCIBLE_EFFECT)
    this->setInvincible(true);
  _ps.push_back(Core::Display.smgr->addParticleSystemSceneNode(false));
  _effects.push_back(AEffect::createEffect(effect, this, static_cast<uint16_t>(_ps.size() - 1)));
}

void 				APlayer::endOfEffect(int id)
{
  _effects.erase(_effects.begin() + id);
  for (size_t i = 0; i < _effects.size(); i++)
    _effects[i]->setId(i);
}

float				APlayer::getSpeed() const
{
  return (_sets->speed / Core::speedRatio);
}

void				APlayer::animIdle()
{
  if (_node->getFrameNr() < 91 || _node->getFrameNr() > 131)
  {
    _node->setFrameLoop(91, 131);
    _node->setAnimationSpeed(20);
  }
}

void				APlayer::animRunning()
{
  if (_node->getFrameNr() < 1 || _node->getFrameNr() > 81)
  {
    _node->setFrameLoop(1, 81);
    _node->setAnimationSpeed(100);
  }
}

void				APlayer::animJump()
{
  if (_node->getFrameNr() < 141 || _node->getFrameNr() > 161)
  {
    _node->setFrameLoop(141, 161);
    _node->setAnimationSpeed(30);
  }
}

void				APlayer::animDab()
{
  if (_node->getFrameNr() < 171 || _node->getFrameNr() > 201)
  {
    _node->setFrameLoop(171, 201);
    _node->setAnimationSpeed(20);
  }
}

void				APlayer::animBoom()
{
  if (_node->getFrameNr() < 211 || _node->getFrameNr() > 241)
  {
    _node->setFrameLoop(211, 241);
    _node->setAnimationSpeed(20);
  }
}

void				APlayer::animCrazzy()
{
  if (_node->getFrameNr() < 241 || _node->getFrameNr() > 275)
  {
    if (!_node->setFrameLoop(241, 275))
    _node->setAnimationSpeed(20);
  }
}
