/**
 * @Author: raph
 * @Date:   2017-06-17T18:53:11+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T02:17:09+02:00
 */



//
// Created by wurtz on 16/05/17.
//

#ifndef AENTITY_HPP
# define AENTITY_HPP

#include <memory>
#include <vector>
#include "Indie.hpp"
#include "MovementManager.hpp"
#include "AEffect.hpp"

class Tile;
class APlayer;

class AEntity : public std::enable_shared_from_this<AEntity>
{
  protected:
    IAnimatedMeshSceneNode			          *_node;
    Tile					                        *_tile;
    APlayer					                      *_player;
    std::vector<IParticleSystemSceneNode *> _ps;
    std::vector<std::unique_ptr<AEffect>>	_effects;
    std::unique_ptr<MovementManager>		  _mov;
    Indie::Entity 				                _type;
    vector3df					                    _pos;

  protected:
    void init(Indie::Entity entity, bool light = true, bool texture = true);

  public:
    virtual ~AEntity() {};

    virtual void 				onFlameHit() {};
    virtual void				update() = 0;

    virtual bool 				foulOfPlayerMoves() const { return false; }
    inline Tile				*getTile() { return _tile; }
    inline vector3df 			&getPos() { return _pos; }
    inline IAnimatedMeshSceneNode		*getNode() { return _node; }
    inline Indie::Entity 			    getType() const { return _type; }
    inline Indie::Direction			getDirection() const { return _mov->getDirection(); }
    inline IParticleSystemSceneNode	*getParticuleSystem(int i = 0) const { return _ps.at(i); }

    void          			initParticlePower();
    void	 				setPos(const vector3df newPos);
    void	 				setForcePos(const vector3df newPos);
    void					addMovement(Indie::Movement mov) { if (_mov) _mov->addMovement(mov); }

    virtual bool				operator==(const Indie::Entity type) { return _type == type; };
    virtual bool				operator==(const std::shared_ptr<AEntity> &oth) { return *oth == _type; };

    static AEntity 			*createEntity(Indie::Entity entity, Tile &tile, APlayer *player, Indie::Biome);
    static Indie::Biome                   _biome;
};

#endif /* !AENTITY_HPP */
