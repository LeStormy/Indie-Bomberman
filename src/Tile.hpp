/**
 * @Author: raph
 * @Date:   2017-06-17T21:45:26+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T02:11:37+02:00
 */

#ifndef ATILE_HPP
#define ATILE_HPP

#include <memory>
#include <map>
#include "Indie.hpp"
#include "Settings.hpp"
#include "Input.hpp"

class AEntity;
class APlayer;
class MapHandler;

class Tile
{
  private:
    // Can't add on / poser / deplacer
    std::map<Indie::Entity, const std::vector<Indie::Entity>> _addEntityRule = {
      {Indie::BOMB_ENTITY, {Indie::FROZENBOMB_ENTITY, Indie::OILBOMB_ENTITY,
			     Indie::BOMB_ENTITY, Indie::BREAKABLE_ENTITY,
			     Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::FROZENBOMB_ENTITY, {Indie::FROZENBOMB_ENTITY, Indie::OILBOMB_ENTITY,
				   Indie::BOMB_ENTITY, Indie::BREAKABLE_ENTITY,
				   Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::OILBOMB_ENTITY, {Indie::FROZENBOMB_ENTITY, Indie::OILBOMB_ENTITY,
				Indie::BOMB_ENTITY, Indie::BREAKABLE_ENTITY,
				Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::FLAME_ENTITY, {Indie::FLAME_ENTITY, Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::POWERSPEED_ENTITY, {Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::POWERKICK_ENTITY, {Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::OIL_ENTITY, {Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::INVINCIBLE_ENTITY, {Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}},
      {Indie::ICE_ENTITY, {Indie::UNBREAKABLE_ENTITY, Indie::FALL_ENTITY}}
    };
    // Can cross / dans le cas ou on peut pas placer, alors on essaye de traverser / stop range
    std::map<Indie::Entity, const std::vector<Indie::Entity>> _crossEntityRule = {
      {Indie::BOMB_ENTITY, {Indie::BREAKABLE_ENTITY, Indie::UNBREAKABLE_ENTITY,
			     Indie::BOMB_ENTITY, Indie::MAGNET_ENTITY, Indie::FALL_ENTITY}},
      {Indie::FROZENBOMB_ENTITY, {Indie::BREAKABLE_ENTITY, Indie::UNBREAKABLE_ENTITY,
				   Indie::BOMB_ENTITY, Indie::MAGNET_ENTITY, Indie::FALL_ENTITY}},
      {Indie::FLAME_ENTITY, {Indie::BREAKABLE_ENTITY, Indie::UNBREAKABLE_ENTITY,
			      Indie::MAGNET_ENTITY, Indie::FALL_ENTITY}},
      {Indie::MAGNET_ENTITY, {Indie::BREAKABLE_ENTITY, Indie::UNBREAKABLE_ENTITY,
			       Indie::MAGNET_ENTITY, Indie::FALL_ENTITY}}
    };
    // Can delete
    std::map<Indie::Entity, const std::vector<Indie::Entity>> _deleteEntityRule = {
      {Indie::BOMB_ENTITY, {Indie::INVINCIBLE_ENTITY, Indie::RANGEUP_ENTITY,
			     Indie::RANGEDOWN_ENTITY, Indie::BOMBFREEZER_ENTITY,
			     Indie::BOMBOILER_ENTITY, Indie::BOMBCUP_ENTITY,
			     Indie::BOMBDOWN_ENTITY, Indie::POWERKICK_ENTITY,
			     Indie::POWERSPEED_ENTITY, Indie::INVINCIBLE_ENTITY}},
      {Indie::FROZENBOMB_ENTITY, {}},
      {Indie::FALL_ENTITY, {Indie::BOMB_ENTITY,
			     Indie::FROZENBOMB_ENTITY,
			     Indie::OILBOMB_ENTITY,
			     Indie::FLAME_ENTITY,
			     Indie::OIL_ENTITY,
			     Indie::ICE_ENTITY,
			     Indie::SPIKE_ENTITY,
			     Indie::TRAMPOLINE_ENTITY,
			     Indie::UNBREAKABLE_ENTITY,
			     Indie::UNBREAKABLE_BORDER_ENTITY,
			     Indie::BREAKABLE_ENTITY,
			     Indie::STONE_ENTITY,
			     Indie::MAGNET_ENTITY,
			     Indie::GROUND_ENTITY,
			     Indie::GRASS_ENTITY,
			     Indie::VOID_ENTITY,
			     Indie::BONUS_ENTITY,
			     Indie::POWERSPEED_ENTITY,
			     Indie::POWERKICK_ENTITY,
			     Indie::RANGEUP_ENTITY,
			     Indie::RANGEDOWN_ENTITY,
			     Indie::BOMBCUP_ENTITY,
			     Indie::BOMBDOWN_ENTITY,
			     Indie::INVINCIBLE_ENTITY,
			     Indie::BOMBFREEZER_ENTITY,
			     Indie::BOMBOILER_ENTITY}},
      {Indie::OILBOMB_ENTITY, {}},
      {Indie::FLAME_ENTITY, {Indie::BOMB_ENTITY, Indie::BREAKABLE_ENTITY,
			      Indie::ICE_ENTITY, Indie::OIL_ENTITY, Indie::INVINCIBLE_ENTITY,
			      Indie::RANGEUP_ENTITY, Indie::RANGEDOWN_ENTITY,
			      Indie::FROZENBOMB_ENTITY, Indie::OILBOMB_ENTITY,
			      Indie::BOMBFREEZER_ENTITY, Indie::BOMBOILER_ENTITY,
			      Indie::BOMBCUP_ENTITY, Indie::BOMBDOWN_ENTITY,
			      Indie::POWERKICK_ENTITY, Indie::POWERSPEED_ENTITY}}
    };

  private:
    uint16_t						_id;
    vector3df 						_pos;
    bool						_reachable;
    float 						_timeToDie;
    int 						_attractivity;
    std::vector<Indie::Entity>				_toDelete;
    std::vector<std::pair<Indie::Entity, APlayer *>>	_toInsert;
    std::array<APlayer *, 4> 				_players;
    bool 						_destroyed = false;
    std::vector<std::shared_ptr<AEntity>> 		_entities;
    std::vector<std::shared_ptr<AEntity>> 		_entitiesDecor;
    MapHandler						*_mapHandler;
    Indie::Biome _biome;

  private:
    void						refactorEntities(const std::vector<Indie::Entity> &dItem);
    void 						insertEntities();

  public:
    Tile(std::vector<Indie::Entity> *entities, MapHandler &mapHandler, uint16_t id, uint16_t floor, Indie::Biome biome);
    ~Tile() { _destroyed = true; };

    void					update();

    inline void						setReachable(bool reachable) { _reachable = reachable; }
    inline bool						getReachable() const { return _reachable; }
    inline bool 					getValid() const { return !_destroyed; }
    AEntity 						*getEntityIfOn(const Indie::Entity type);
    bool 						isEntitiesExisting(const std::vector<Indie::Entity> &types) const;
    bool                        			isEntitiesOnTile(const Indie::Entity entity);
    void 						flameHit();

    bool						addEntity(const Indie::Entity type, APlayer *player);
    bool						addEntity(std::shared_ptr<AEntity> entity) { _entities.push_back(entity); return true; };
    bool						checkAddEntity(const Indie::Entity type);
    void						deleteEntities(const std::vector<Indie::Entity> &type);
    bool						crossEntity(const Indie::Entity type, bool moving = false);

    inline void						setPlayer(APlayer *player, uint16_t id) { _players[id] = player; }
    inline std::array<APlayer *, 4>			&getPlayers() { return _players; };

    inline void						setTimeToDie(float timer) { _timeToDie > timer || _timeToDie == -1.0f || timer == -1.0f ? _timeToDie = timer : 0; }
    inline float 					getTimeToDie() const { return _timeToDie; }

    inline void 					addAttractivity(int value) { _attractivity += value; }
    inline int						getAttractivity() const { return _attractivity; }

    inline uint16_t 					getId() const { return _id; }
    inline const vector3df				&getPos() const { return _pos; }
    vector3df						getPosCenter();
    inline MapHandler 					*getMapHandler() { return _mapHandler; }

    inline const std::vector<Indie::Entity>		&getDeleteEntityRule(const Indie::Entity type) { return _deleteEntityRule[type]; }
};

#endif /* !ATILE_HPP */
