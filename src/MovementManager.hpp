//
// Created by baptiste on 6/5/17.
//

#ifndef INDIESTUDIO_MOVEMENT_HPP
#define INDIESTUDIO_MOVEMENT_HPP

#include <memory>
#include "Indie.hpp"

class APlayer;
class AEntity;
class Tile;

class AMovement
{
  protected:
    APlayer 			*_player = nullptr;
    AEntity			*_entity = nullptr;
    Tile			*_destTile = nullptr;
    Indie::Direction		_direction;
    Indie::Movement 		_type;
    bool 			_posReseted;

  protected:
    void			setPlayerDestTile();
    void			setEntityDestTile();
    inline void			centerPlayerPos();
    void			prepareToMove();

  public:
    virtual ~AMovement() {}

    virtual bool		update() = 0;
    inline Indie::Movement	getType() const { return _type; }
    inline Indie::Direction	getDirection() const { return _direction; }
    virtual bool		canBeChanged(Indie::Movement mov) = 0;
};

class MovementManager
{
  protected:
    APlayer 				*_player = nullptr;
    AEntity				*_entity = nullptr;
    std::unique_ptr<AMovement>		_move = nullptr;

  public:
    MovementManager(APlayer *player) : _player(player) {}
    MovementManager(AEntity *entity) : _entity(entity) {}
    ~MovementManager() = default;

    void			addMovement(Indie::Movement move);
    void			update();

    Indie::Direction		getDirection() const;
};

#endif //INDIESTUDIO_MOVEMENT_HPP
