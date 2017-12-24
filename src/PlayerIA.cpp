#include "PlayerIA.hpp"
#include "Core.hpp"

void        PlayerIA::setWeight(Indie::PlayerType  type)
{
    switch  (type)
    {
        case Indie::PlayerType::IA_PLAYER_EZ :
            _defaultAtkWeight = 1;
            _incModifAtkWeight = 1;
            _defaultDefWeight = 0;
            _incModifDefWeight = 2;
            _defaultFarmWeight = 10;
            _incModifFarmWeight = 2;
            break;
        case Indie::PlayerType::IA_PLAYER_MED :
            _defaultAtkWeight = 0;
            _incModifAtkWeight = 3;
            _defaultDefWeight = 0;
            _incModifDefWeight = 7;
            _defaultFarmWeight = 0;
            _incModifFarmWeight = 1;
            break;
        case Indie::PlayerType::IA_PLAYER_HARD :
            _defaultAtkWeight = 3;
            _incModifAtkWeight = 2;
            _defaultDefWeight = 1;
            _incModifDefWeight = 3;
            _defaultFarmWeight = 0;
            _incModifFarmWeight = 6;
            break;
        default:
            break;
    }
}

PlayerIA::PlayerIA(PlayerSet &playerSet, MapHandler *map, PlayersManager *playerManager, Indie::PlayerType type)
        : playersManager(playerManager), _wait(_noDanger), _modifDefWeight(0), _modifAtkWeight(0), _modifFarmWeight(0)
{
    _sets = &playerSet;
    _mapHandler = map;
    init();
    animIdle();
    _bombType = Indie::BombType::CLASSIC_BOMB;
    _timeSinceLastAction = _reactivity;
    _previousOrder = Order::FARM_POW;
    _currentAction = Action::WAIT;
    _currentOrder = Order::FARM_INT;
    setWeight(type);
}

bool        PlayerIA::simulateReflex()
{
    if (_timeSinceLastAction >= _reactivity)
    {
        _timeSinceLastAction = 0;
        return (true);
    }
    _timeSinceLastAction += Core::frameRate;
    if (_wait > 0)
        _wait -= Core::frameRate;
    return (false);
}

void                    PlayerIA::update()
{
    if (_sets->alive)
    {
        _atkRange = static_cast<float>(_sets->bombRange - 1);
        if (simulateReflex())
            updateOrder();
        else if (_wait > 0)
        {
            float   danger = getTile()->getTimeToDie();

            if (danger != _noDanger && danger <= _safeZone)
                setOrderDef();
            _wait -= Core::frameRate;
        }
        else
        {
            updateAction();
            doAction();
        }
        if (_currentAction == Action::WAIT
            || (_currentAction == Action::BOMB && getTile()->getPosCenter().X == _sets->position.X
                && getTile()->getPosCenter().Z == _sets->position.Z))
            animIdle();
        else
            _mov->update();
        for (uint16_t i = 0; i < _effects.size(); i++)
            _effects[i]->update();
        if (_previousOrder == _currentOrder)
            ++_modifAtkWeight;
        else
            _previousOrder = _currentOrder;
    }
}

void        PlayerIA::updateOrder()
{
    float   danger = getTile()->getTimeToDie();

    _atkWeight = _defaultAtkWeight;
    _defWeight = _defaultDefWeight;
    _farmWeight = _defaultFarmWeight;

    if (_modifAtkWeight > 100 || _modifFarmWeight > 100 || _modifDefWeight > 100)
    {
        _modifAtkWeight /= 100;
        _modifDefWeight /= 100;
        _modifFarmWeight /= 100;
    }
    if (danger != _noDanger && danger <= _safeZone)
    {
        _defWeight +=  _incModifDefWeight;
        _modifAtkWeight = 0;
        _modifFarmWeight = 0;
    }
    else if (_currentAction == Action::WAIT && _wait > 0)
        _wait -= Core::frameRate;
    else if (isPlayerNearBy() <= _atkRange)
    {
        _modifAtkWeight += _incModifAtkWeight;
        _modifFarmWeight = 0;
    }
    else
        _farmWeight += 3;
    _atkWeight += _modifAtkWeight;
    _defWeight += _modifDefWeight;
    _farmWeight += _modifFarmWeight;
    if (_defWeight >= _atkWeight && _defWeight >= _farmWeight)
        setOrderDef();
    else if (_atkWeight >= _farmWeight)
        setOrderAtk();
    else
        setOrderFarm();
}

void        PlayerIA::updateAction()
{
    if (_currentPath.size() != 0)
        if (getTile()->getPos().X == _currentPath[0]->getPos().X
            && getTile()->getPos().Z == _currentPath[0]->getPos().Z)
        {
            _currentPath.pop_front();
            if (_currentPath.size() == 0)
            {
                if (_currentOrder == Order::FARM_INT || _currentOrder == Order::ATK)
                    _currentAction = Action::BOMB;
                else if (_currentOrder == Order::DEF)
                    _currentAction = Action::WAIT;
            }
        }
}

bool        PlayerIA::canINuke()
{
    int     i = -1;
    bool    stop = false;
    scanTile    *interrest = nullptr;

    if (_sets->bombCount <= 0)
        return (false);
    if (getBombType() != Indie::BombType::CLASSIC_BOMB)
        return (true);
    if (getTile()->getTimeToDie() < _safeZone && getTile()->getTimeToDie() != _noDanger)
        return (false);
    initScan();
    while (scan() && ++i < 5 && !(stop = findInterest(getTile(), interrest)));
    if (stop == true)
    {
        setPath(interrest);
        _defWeight +=  _incModifDefWeight;
        _currentOrder = Order::DEF;
        _currentAction = Action::MOVE;
    }
    return stop;
}

void        PlayerIA::doAction()
{
    if (_currentAction == Action::BOMB)
    {
        if (canINuke())
            dropBomb();
    }
    else if (_sets->bombCount == 0)
    {
        _currentAction = Action::MOVE;
    }
    else if (_currentPath.size() == 0)
    {
        _currentAction = Action::WAIT;
    }
    else if (_currentAction == Action::MOVE)
        doActionMove();
}

void        PlayerIA::doActionMove()
{
    if (getTile()->getPos().X > _currentPath[0]->getPos().X)
        move(Indie::ActionPlayer::LEFT_ACTION_PLAYER);
    else if (getTile()->getPos().X < _currentPath[0]->getPos().X)
        move(Indie::ActionPlayer::RIGHT_ACTION_PLAYER);
    else if (getTile()->getPos().Z > _currentPath[0]->getPos().Z)
        move(Indie::ActionPlayer::DOWN_ACTION_PLAYER);
    else if (getTile()->getPos().Z < _currentPath[0]->getPos().Z)
        move(Indie::ActionPlayer::UP_ACTION_PLAYER);
}

void        PlayerIA::setOrderDef()
{
    bool    scanResult = false;
    size_t  stop = -1;
    scanTile *interrest = nullptr;

    if (_currentPath.size() != 0 && _currentAction == Action::MOVE
        && (_currentPath[0]->getTimeToDie() == _noDanger
            || _currentPath[0]->getTimeToDie() > _safeZone))
        return ;
    if (getTile()->getTimeToDie() == _noDanger)
    {
        _currentOrder = Order::FARM_INT;
        return ;
    }
    initScan();
    while (scan() && ++stop < 5)
        if ((scanResult = findInterest(interrest, 2.0f)))
            break;
    if (scanResult == false)
        findInterest(interrest, 2.0f);
    _currentOrder = Order::DEF;
    _currentAction = Action::MOVE;
    setPath(interrest);
}

void        PlayerIA::setOrderFarm()
{
    Order               previous = _currentOrder;
    scanTile            *interrest = nullptr;
    size_t              stop = -1;

    _currentOrder = Order::FARM_INT;
    initScan();
    while (scan() && ++stop < 12)
    {
        if (findInterest(interrest))
        {
            _currentOrder = Order::FARM_POW;
            break;
        }
    }
    if (interrest == nullptr && previous != Order::ATK && previous != Order::ATK_GETCLOSER)
        return (setOrderAtk());
    else if (interrest == nullptr)
        return (setOrderDef());
    _modifFarmWeight += _incModifFarmWeight;
    setPath(interrest);
    _currentAction = Action::MOVE;
}

void                    PlayerIA::setOrderAtk()
{
    scanTile    *interrest = nullptr;
    size_t      stop = -1;
    int         range;

    range = isPlayerNearBy();
    initScan();
    while (scan() && ++stop < _atkRange)
    {
        if (findInterest(getNearbyPlayer(), interrest))
        {
            if ((range < _sets->bombRange - 1)
                && ((interrest->_tile->getPosCenter().X >= _sets->position.X - 0.5
                     && interrest->_tile->getPosCenter().X <= _sets->position.X + 0.5)
                    || (interrest->_tile->getPosCenter().Z >= _sets->position.Z - 0.5
                        && interrest->_tile->getPosCenter().Z <= _sets->position.Z + 0.5)))
                {
                    _currentOrder = Order::ATK;
                    _currentAction = Action::BOMB;
                    return ;
                }
            _currentOrder = Order::ATK;
            _currentAction = Action::MOVE;
            setPath(interrest);
            return ;
        }
    }
    if (interrest == nullptr || _currentOrder == Order::ATK_GETCLOSER)
    {
        _currentOrder = Order::ATK_GETCLOSER;
        _modifFarmWeight += _modifAtkWeight;
        setOrderFarm();
        return ;
    }
    _currentAction = Action::MOVE;
    _currentOrder = Order::ATK_GETCLOSER;
    setPath(interrest);
}
