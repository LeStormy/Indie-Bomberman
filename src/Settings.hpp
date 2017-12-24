/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-29T13:22:00+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T01:34:49+02:00
 */
//
// Created by wurtz on 16/05/17.
//

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <unordered_map>
#include "Input.hpp"
#include "Indie.hpp"
#include "HashType.hpp"

struct MapImage
{
  std::vector<uint32_t>		map;

  template <typename T>
  void setMesh(const T meshType, const unsigned char meshNb, const int index)
  {
    if (!(map[index] & 1))
      map[index] |= 1;
    map[index] |= (meshType << (8 * (meshNb)));
    return ;
  }

  uint16_t getFloor(const int index)
  {
    if (map[index] <= 1)
      return (0);
    else if (map[index] <= 0xFFFF)
      return (1);
    else if (map[index] <= 0xFFFFFF)
      return (2);
    else
      return (3);
  }
};

struct MapSet
{
  std::vector<std::vector<Indie::Entity>> newtiles;
  MapImage			mapImage;
  std::pair<size_t, size_t>	mapSize;
  size_t			blockDensity;
  std::vector<size_t> 		subBlockDensity;
  size_t			floorDensity;
  std::vector<size_t> 		subFloorDensity;
  bool				platforms;
  Indie::Biome Biome;
//  int				premadeIndex;
};

struct PlayerSet
{
  Indie::PlayerType		playerType = Indie::UNUSED_PLAYER;
  KeyMap			keyMap;
  float				speed;
  std::string			name;
  bool 				alive;
  vector3df			position;
  uint8_t 			bombCount; // Nombres de bombes maximum
  uint16_t 			bombRange;
  uint8_t			bombUp; // Nombre de bombe qu'il peux encore poser
  uint8_t 			id;
  size_t      score;
};

struct HUDSet
{
  unsigned int						timer;
  std::chrono::duration<double>				elapsed;
  std::chrono::time_point<std::chrono::system_clock>	gameDate;
};

struct Settings
{
  int				magic = 0xBADA55;
  MapSet			mapSet;
  std::array<PlayerSet, 4>	players;
  HUDSet			hudSet;
};

struct SoundSets
{
  int				MasterVolume;
  int				MusicVolume;
  int				FXVolume;
  bool				Mute;
};

typedef std::unordered_map<Indie::ScoreType, std::vector<std::pair<std::string, size_t>>, HashType<Indie::ScoreType>> ScoreMap;

struct ScoreBoard {

};

struct SAppContext
{
  IrrlichtDevice *device;
  Settings *settings;
};

#endif /* !SETTINGS_HPP */
