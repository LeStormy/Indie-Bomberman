/**
 * @Author: raph
 * @Date:   2017-06-14T16:07:49+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:53:52+02:00
 */

#include <algorithm>
#include "AEntity.hpp"
#include "Tile.hpp"
#include "MapHandler.hpp"
#include "Core.hpp"

Tile::Tile(std::vector<Indie::Entity> *entities, MapHandler &mapHandler, uint16_t id, uint16_t floor, Indie::Biome biome)
{
  _mapHandler = &mapHandler;
  _biome = biome;
  _id = id;
  _timeToDie = -1.0f;
  _attractivity = 0;
  _reachable = true;
  for (auto &it : _players)
    it = nullptr;
  _pos.X = static_cast<float>(getId() % getMapHandler()->getWidth());
  _pos.Z = static_cast<float>(getId() / getMapHandler()->getWidth());
  _pos.Y = floor;
  for (auto &entity : *entities)
  {
    _entities.push_back(std::shared_ptr<AEntity>());
    _entities.back().reset(AEntity::createEntity(entity, *this, nullptr, _biome));
  }
  int r = rand() % 6;
  for (uint16_t i = 0; i < r; i++)
  {
    _entitiesDecor.push_back(std::shared_ptr<AEntity>());
    _entitiesDecor.back().reset(AEntity::createEntity(Indie::GROUND_ENTITY, *this, nullptr, _biome));
    _entitiesDecor.back().get()->setForcePos({_pos.X + 0.5f, static_cast<float>(floor - i), _pos.Z + 0.5f});
  }
}

void			Tile::update()
{
  for (auto & it : _entities)
    if (it)
      it->update();
  refactorEntities(_toDelete);
  insertEntities();
  _toDelete.clear();
}

AEntity			*Tile::getEntityIfOn(Indie::Entity type)
{
  auto it = std::find_if(_entities.begin(), _entities.end(),
			 [&] (std::shared_ptr<AEntity> &entity)
			 { return *entity == type; });
  if (it != _entities.end())
  {
    return (it->get());
  }
  return (nullptr);
}

vector3df		Tile::getPosCenter()
{
  vector3df		pos = _pos;

  pos.X += 0.5f;
  pos.Z += 0.5f;
  return pos;
}

bool 			Tile::isEntitiesExisting(const std::vector<Indie::Entity> &types) const
{
  for (auto &type : types)
    for (auto &entity : _entities)
      if (entity && *(entity.get()) == type)
	return true;
  return false;
}

bool            Tile::isEntitiesOnTile(const Indie::Entity entity)
{
  for (auto & ite : _entities)
  {
    if (ite.get()->getType() == entity)
      return (true);
  }
  return (false);
}

void 			Tile::flameHit()
{
  std::for_each(_entities.begin(), _entities.end(),
		[] (std::shared_ptr<AEntity> &entity)
		{ entity->onFlameHit(); } );
}

bool			Tile::addEntity(const Indie::Entity type, APlayer *player)
{
  if (!checkAddEntity(type))
    return false;
  for (auto &rule : _addEntityRule[type])
    for (auto &entity : _toInsert)
      if (entity.first == rule)
	return false;
  _toInsert.push_back(std::make_pair<const Indie::Entity&, APlayer *&>(type, player));
  return true;
}

void 			Tile::insertEntities()
{
  for (auto & it : _toInsert) {
    if (!checkAddEntity(it.first))
      continue ;
    _entities.insert(_entities.begin(), std::shared_ptr<AEntity>());
    _entities.front().reset(AEntity::createEntity(it.first, *this, it.second, _biome));
  }
  _toInsert.clear();
}

bool			Tile::checkAddEntity(const Indie::Entity type)
{
  for (auto &rule : _addEntityRule[type])
    for (auto &entity : _entities)
      if (entity && *(entity.get()) == rule)
	return false;
  return true;
}

void			Tile::deleteEntities(const std::vector<Indie::Entity> &type)
{
  _toDelete.insert(_toDelete.end(), type.begin(), type.end());
  _toDelete.erase(std::unique(_toDelete.begin(), _toDelete.end()), _toDelete.end());
}

bool			Tile::crossEntity(const Indie::Entity type, bool moving)
{
  for (auto &rule : _crossEntityRule[type])
    for (auto &entity : _entities)
      if (*(entity.get()) == rule)
	return false;
  if (moving)
    for (auto &it : _players)
      if (it != nullptr)
	return (false);
  return true;
}

void			Tile::refactorEntities(const std::vector<Indie::Entity> &dItem)
{
  _entities.erase(std::remove_if(_entities.begin(), _entities.end(),
				 [&](std::shared_ptr<AEntity> &entity)
				 { return (std::any_of(dItem.begin(), dItem.end(),
						       [&entity] (Indie::Entity type)
						       { return *entity == type; })); }),
		  _entities.end());
}
