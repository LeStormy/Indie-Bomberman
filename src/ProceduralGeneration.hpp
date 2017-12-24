//
// Created by yan on 25/05/17.
//

#ifndef PROCEDURALGENERATION_HPP
#define PROCEDURALGENERATION_HPP

#include <vector>
#include "Settings.hpp"

class ProceduralGeneration
{
public:
    ProceduralGeneration(MapSet & map);
    ~ProceduralGeneration();
    void        generateMap();

private:
    std::vector<Indie::Entity>  &    getTile(size_t y, size_t x);
    std::vector<Indie::Entity> &     getRealTile(size_t y, size_t x);
    void                             lockPlayerStart();
    void                             setLockEmpty(std::vector<Indie::Entity> & tile);
    void                             setPlatform(size_t y, size_t x, size_t w, size_t h, size_t nbAccess);
    void                             setPlatformNext(size_t y, size_t x, size_t w, size_t h, size_t rand, size_t & i);
    void                             setHeight(size_t y, size_t x);
    void                             setTrampo(size_t y, size_t x, size_t & cnt, char platFormSide);
    void                             setTrampoNext(char platFormSide, size_t y, size_t x);
    void                             horizontalPlatForm();
    void                             verticalPlatForm();
    void                             midPlatForm();
    void                             generatePlatform();
    void                             generateModWUnbreakable(size_t lastHIndex, size_t lastWIndex);
    void                             generateUnbreakable();
    void                             generateWUnbreakable(size_t cnt);
    void                             setItem(std::vector<Indie::Entity> & tile);
    bool                             isHigh(size_t y, size_t x);
    bool                             clearTrampo(size_t y, size_t x, char platformside);
    bool                             checkWay(size_t y, size_t x, char platformside);
    bool                             setUnbreakable(size_t y, size_t x);
    bool                             whatEntity(std::vector<Indie::Entity> tile, Indie::Entity type);

private:
    MapSet      & _map;
    size_t        _height;
    size_t        _width;
    bool          _platform;
};

#endif /* PROCEDURALGENERATION_HPP */