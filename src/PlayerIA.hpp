//
// Created by yan on 13/06/17.
//

#ifndef PLAYERIA_HPP
#define PLAYERIA_HPP

#include <deque>
#include "APlayer.hpp"
#include "PlayersManager.hpp"

struct scanTile
{
    std::shared_ptr<Tile>       _tile;
    std::shared_ptr<scanTile>   _parent;
    float                       _eta;
};

enum    Order
{
    FARM_POW,
    FARM_INT,
    DEF,
    ATK,
    ATK_GETCLOSER
};

enum    Action
{
    MOVE,
    WAIT,
    BOMB
};

class   PlayerIA : public APlayer
{

public:
    PlayerIA(PlayerSet &playerSet, MapHandler *map, PlayersManager *playersManager, Indie::PlayerType type);
    virtual ~PlayerIA() {};
    void        update();

private:
    PlayersManager                          *playersManager;
    enum Action                             _currentAction;
    enum Order                              _currentOrder;
    enum Order                              _previousOrder;
    float                                   _wait;
    float                                   _timeSinceLastAction;
    std::deque<std::shared_ptr<Tile>>       _currentPath;
    std::vector<std::shared_ptr<scanTile>>  _scanedTile;

    float                                   _atkRange;
    size_t                                  _startScan;

    void                    setWeight(Indie::PlayerType  type);
    bool                    simulateReflex();
    void                    updateOrder();
    bool                    canINuke();
    void                    setOrderDef();
    void                    setOrderFarm();
    void                    setOrderAtk();
    void                    updateAction();
    void                    doAction();
    void                    doActionMove();

    void                    initScan();
    bool                    scan();
    bool                    isTileValid(std::shared_ptr<Tile> &tile, std::shared_ptr<scanTile> &parent);
    void                    addTile(std::shared_ptr<Tile> &newTile, std::shared_ptr<scanTile> parent, float eta);
    float                   calculateEta(std::shared_ptr<scanTile> &tile);
    void                    setPath(scanTile *start);
    float                   isTileSafe(std::shared_ptr<scanTile> tile);
    bool                    checkTile(std::shared_ptr<scanTile> tile, float x, float z);
    bool                    findInterest(Tile *self, scanTile *& best);
    bool                    findInterest(scanTile *&best);
    bool                    findInterest(scanTile *& best, float dangerLevel);
    bool                    findInterest(std::shared_ptr<Tile> nearByPlayer, scanTile *&best);
    int                     getDist(std::shared_ptr<Tile> src, std::shared_ptr<Tile> dest);
    std::shared_ptr<Tile>   getNearbyPlayer();
    int                     isPlayerNearBy();

    const std::vector<Indie::Entity>        _powerupInterest = {Indie::Entity::POWERKICK_ENTITY,
                                                                Indie::Entity::POWERSPEED_ENTITY,
                                                                Indie::Entity::INVINCIBLE_ENTITY,
                                                                Indie::Entity::RANGEUP_ENTITY,
                                                                Indie::Entity::BOMBCUP_ENTITY};

    const std::vector<Indie::Entity>        _breakable = {Indie::Entity::BREAKABLE_ENTITY};
    const float                             _reactivity = 0.1f;
    const float                             _reactivityLag = 0.2f;
    const float                             _safeZone = 1.0f;
    const float                             _noDanger = -1.0f;

    int                                     _defWeight;
    int                                     _defaultDefWeight;
    int                                     _modifDefWeight;
    int                                     _incModifDefWeight;

    int                                     _atkWeight;
    int                                     _defaultAtkWeight;
    int                                     _modifAtkWeight;
    int                                     _incModifAtkWeight;

    int                                     _farmWeight;
    int                                     _defaultFarmWeight;
    int                                     _modifFarmWeight;
    int                                     _incModifFarmWeight;
};

#endif /* PLAYERIA_HPP */
