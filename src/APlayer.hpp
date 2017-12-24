/**
 * @Author: raph
 * @Date:   2017-06-11T17:30:11+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T03:18:00+02:00
 */

#ifndef APLAYER_HPP
#define APLAYER_HPP

#include <memory>
#include <atomic>
#include <array>
#include <algorithm>
#include "Indie.hpp"
#include "Settings.hpp"
#include "MovementManager.hpp"
#include "AEffect.hpp"
//#include "Core.hpp"

class Tile;
class MapHandler;

class APlayer
{
  protected:
    MapHandler					*_mapHandler;
    uint16_t					_idTile;
    std::unique_ptr<MovementManager>		_mov;
    std::vector<std::unique_ptr<AEffect>>	_effects;
    Indie::BombType 				_bombType;
    IAnimatedMeshSceneNode			*_node;
    std::vector<IParticleSystemSceneNode *>	_ps;
    PlayerSet					*_sets;
    bool					_invicible = false;
    Indie::Direction				_direction;
    bool 					_anim;

  public:
    virtual ~APlayer() {
      _sets->alive = true;
      if (!_effects.empty())
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
      //TODO: RESET OTHER SETTINGS
    }

    virtual void			update() = 0;

    void 				init();

    void				move(Indie::ActionPlayer);
    void				dropBomb();
    void 				killMe(bool force = false);

    inline void				setSpeed(const float speed) { _sets->speed = speed; }
    void				setPos(const vector3df pos);
    void 			        setInvincible(const bool state);
    inline void 			setBombType(Indie::BombType bombType) { _bombType = bombType; }
    inline void				incBombMax(void) { ++_sets->bombCount; ++_sets->bombUp; }
    inline void				setAnim(bool anim) { _anim = anim; }
    inline void				decBombMax(void)
    {
      if (_sets->bombCount > 1)
	--_sets->bombCount;
    }
    inline void				incBombRange(void) { ++_sets->bombRange; }
    inline void				decBombRange(void)
    {
      if (_sets->bombRange > 1)
	--_sets->bombRange;
    }
    inline void				incBombCnt(void)
    {
      if (_sets->bombUp < _sets->bombCount)
	++_sets->bombUp;
    }
    inline void				decBombCnt(void)
    {
      if (_sets->bombUp > 0)
	--_sets->bombUp;
    }

    float				getSpeed() const;
    inline float			getRealSpeed() const { return _sets->speed; };
    inline vector3df			getPos() const { return (_sets->position); }
    inline uint8_t			getId() const { return (_sets->id); }
    inline const std::string		getName() const { return (_sets->name); }
    inline uint16_t 			getBombRange() const { return (_sets->bombRange); }
    inline uint16_t 			getBombCount() const { return (_sets->bombCount); }
    inline bool				getBombUp() const { return (0 < _sets->bombUp); }
    inline bool				getAlive() const { return _sets->alive; }
    inline Indie::BombType 		getBombType() const { return _bombType; }
    inline bool				getInvincible() const { return _invicible; }
    inline uint16_t 			getIdTile() const { return _idTile; }
    inline bool 			hasBonus(Indie::EffectType type) const {
      return std::find_if(_effects.begin(), _effects.end(),
			  [type] (const std::unique_ptr<AEffect> &effect)
			  { return *effect == type; }) != _effects.end();
    }
    inline MapHandler			*getMapHandler() const { return _mapHandler; }
    inline IAnimatedMeshSceneNode	*getNode() const { return _node; }
    inline IParticleSystemSceneNode	*getParticuleSystem(int i = 0) const { return _ps.at(i); }

    inline size_t 			getEffectRunningNr() const { return _effects.size(); }
    Tile				*getTile() const;
    inline Indie::Direction		getDirection() const { return _direction; }

    void				addMovement(Indie::Movement mov) { if (_mov) _mov->addMovement(mov); }
    void				animIdle();
    void				animRunning();
    void				animJump();
    void				animDab();
    void				animBoom();
    void				animCrazzy();

    void				victoryEffect(std::pair<SColor, SColor> playerColor);
    void	 			addEffect(Indie::EffectType effect);
    void 				endOfEffect(int id);
};

#endif /* !APLAYER_HPP */
