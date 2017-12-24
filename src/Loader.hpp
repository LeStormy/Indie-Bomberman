/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-17T15:20:25+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T23:37:43+02:00
 */

#ifndef LOADER_HPP_
# define LOADER_HPP_

#ifdef  linux
#include <unistd.h>
#endif

#ifdef  _WIN32
#include <io.h>
#endif

#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/binary_object.hpp>
#include "Menu.hpp"
#include "Indie.hpp"
#include "Settings.hpp"
#include "Directory.hpp"

class LoadSave {
public:
  LoadSave();
  ~LoadSave() {}

  int loadPremadeMap(size_t index, Settings &settings) const;
  int loadFile(const std::string &path, Settings &settings) const;
  int loadScores(const std::string &path, std::unordered_map<Indie::ScoreType, std::vector<std::pair<std::string, size_t>>, HashType<Indie::ScoreType>> &) const;
  int loadBinds(const std::string &path, KeyMap &, KeyMap &, KeyMap &, KeyMap &) const;

  int serializeMap(const std::string &path, const Settings &settings) const;
  int saveFile(const std::string &path, const Settings &settings) const;
  int saveScores(const std::string &path, const std::unordered_map<Indie::ScoreType, std::vector<std::pair<std::string, size_t>>,	HashType<Indie::ScoreType>> &scoreMap) const;
  int saveBinds(const std::string &path, const std::array<KeyMap, 4> &binds) const;


private:
  std::vector<std::string> premades;
  bool fullCheckMap(const MapSet &mapset) const;
  bool checkCorrupted(const Settings &sets) const;
};

namespace boost {
  namespace serialization {

    template<class Archive>
    void serialize(Archive & ar, SoundSets & g, const unsigned int)
    {
      ar & g.MasterVolume;
      ar & g.MusicVolume;
      ar & g.FXVolume;
      ar & g.Mute;
    }

    template<class Archive>
    void serialize(Archive & ar, Settings & g, const unsigned int)
    {
      ar & g.magic;
      ar & g.players;
      ar & g.mapSet;
      ar & g.hudSet;
    }

    template<class Archive>
    void serialize(Archive & ar, MapSet & g, const unsigned int)
    {
      ar & g.newtiles;
      ar & g.mapImage;
      ar & g.mapSize;
      ar & g.blockDensity;
      ar & g.subBlockDensity;
      ar & g.floorDensity;
      ar & g.subFloorDensity;
      ar & g.platforms;
      ar & g.Biome;
    }

    template<class Archive>
    void serialize(Archive & ar, HUDSet & g, const unsigned int)
    {
      ar & g.timer;
      ar & boost::serialization::make_binary_object(&g.elapsed, sizeof(g.elapsed));
      ar & boost::serialization::make_binary_object(&g.gameDate, sizeof(g.gameDate));
    }

    template<class Archive>
    void serialize(Archive & ar, vector3df & g, const unsigned int)
    {
      ar & g.X;
      ar & g.Y;
      ar & g.Z;
    }

    template<class Archive>
    void serialize(Archive & ar, MapImage & g, const unsigned int)
    {
      ar & g.map;
    }

    template<class Archive>
    void serialize(Archive & ar, PlayerSet & g, const unsigned int)
    {
      ar & g.playerType;
      ar & g.keyMap;
      ar & g.speed;
      ar & g.name;
      ar & g.alive;
      ar & g.position;
      ar & g.bombCount;
      ar & g.bombRange;
      ar & g.bombUp;
      ar & g.id;
      ar & g.score;
    }

    template<class Archive>
    void serialize(Archive & ar, KeyMap & g, const unsigned int)
    {
      ar & g.up;
      ar & g.down;
      ar & g.right;
      ar & g.left;
      ar & g.action;
    }

    template<class Archive>
    void serialize(Archive & ar, dimension2d<s32> & g, const unsigned int)
    {
      ar & g.Width;
      ar & g.Height;
    }
  }
}

#endif //INDIESTUDIO_SETTINGS_HPP
