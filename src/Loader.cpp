/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-17T15:20:09+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T23:24:49+02:00
 */

#include <string.h>
#include <cstdio>
#include "Loader.hpp"
#include "Warning.hpp"
#include "Core.hpp"
#include "Menu.hpp"
#include "MenuScreens.hpp"

# define LOADFILE_SUCCESS 0
# define LOADFILE_NOACCESS 1

# define LOADFILE_CORRUPTED 2

static void changeName(const std::string &)
{
  Menu::reloadScreen = true;
}

static void doNothing(const std::string &)
{
  Menu::reloadScreen = true;
}

LoadSave::LoadSave()
{
  Directory dir;
  premades = dir.getFiles(".map", CONF("Maps/"), false);
}

int LoadSave::loadFile(const std::string &path, Settings &settings) const
{
  std::ifstream ifs(path);
  Settings settingsTmp;
  try {
    boost::archive::text_iarchive ia(ifs);
    ia >> settingsTmp;
  }
  catch ( const boost::archive::archive_exception & ) {
    std::function<void(std::string)> okFnc = &doNothing;
    Core::popUp.create(new Warning <std::string, std::string>(okFnc, okFnc, path, path));
    return LOADFILE_NOACCESS;
  }

  if (settingsTmp.magic != 0xBADA55)
  {
    std::function<void(std::string)> okFnc = &changeName;
    std::function<void(std::string)> dismissFnc = &doNothing;
    Core::popUp.create(new Warning <std::string, std::string>(okFnc, dismissFnc, path, path,
        "This file is corrupted !\nMay I change its extension ?", true, true));
  }

  settings = settingsTmp;

  return LOADFILE_SUCCESS;
}

bool LoadSave::fullCheckMap(const MapSet &mapSet) const
{
  if (mapSet.mapSize.first < 8 || mapSet.mapSize.first > 14
      || mapSet.mapSize.second < 8 || mapSet.mapSize.second > 14
      || mapSet.newtiles.size() != mapSet.mapSize.first * mapSet.mapSize.second
      || mapSet.mapImage.map.size() < mapSet.mapSize.first * mapSet.mapSize.second)
      return false;
  for (size_t i = 0; i < mapSet.newtiles.size(); i++)
  {
    if (mapSet.newtiles[i].size() > 3)
      return false;
    for (uint8_t j = 0; j < mapSet.newtiles[i].size(); j++)
      if (static_cast<int>(mapSet.newtiles[i][j]) < 0
          || static_cast<int>(mapSet.newtiles[i][j]) > static_cast<int>(Indie::ENTITY_COUNT))
          return false;
    if (i < mapSet.mapSize.first
        || i % mapSet.mapSize.first == 0
        || i % mapSet.mapSize.first == mapSet.mapSize.first - 1
        || i > (mapSet.mapSize.second - 1) * mapSet.mapSize.first)
    {
      bool UBK = false;
      for (uint8_t j = 0; j < mapSet.newtiles[i].size(); j++)
        if (mapSet.newtiles[i][j] == Indie::UNBREAKABLE_BORDER_ENTITY)
          UBK = true;
      if (UBK == false)
        return false;
    }
  }
  for (size_t i = mapSet.mapImage.map.size() - mapSet.mapSize.first * mapSet.mapSize.second;
       i < mapSet.mapImage.map.size(); i++)
    if ((mapSet.mapImage.map[i] & 1) != 1)
      return false;
  return true;
}

int LoadSave::loadPremadeMap(size_t index, Settings &settings) const
{
  if (premades.size() == 0)
    return LOADFILE_NOACCESS;
  std::ifstream ifs(CONF("Maps/") + premades[index] + ".map");
  MapSet mapSetTmp;
  try {
    boost::archive::text_iarchive ia(ifs);
    ia >> mapSetTmp;
  }
  catch ( const boost::archive::archive_exception & ) {
    return LOADFILE_NOACCESS;
  }
  if (!this->fullCheckMap(mapSetTmp))
  {
    std::string path(CONF("Maps/") + premades[index] + ".map");
    std::function<void(const std::string &)> ok = &changeName;
    std::function<void(const std::string &)> cancel = &doNothing;
    Core::popUp.create(new Warning<const std::string &, const std::string &>(ok,cancel, path, path, "This map file is corrupted !", true, false));
    Menu::reloadScreen = false;
    Menu::ResetPlayers(settings, {10,10});
    return LOADFILE_NOACCESS;
  }
  settings.mapSet = mapSetTmp;
  return LOADFILE_SUCCESS;
}

int LoadSave::loadScores(const std::string &path, std::unordered_map<Indie::ScoreType, std::vector<std::pair<std::string, size_t>>, HashType<Indie::ScoreType>> &scoreMap) const
{
  std::ifstream ifs(path);
  try {
    boost::archive::text_iarchive ia(ifs);
    ia >> scoreMap;
  }
  catch ( const boost::archive::archive_exception & ) {
    return LOADFILE_NOACCESS;
  }

  return LOADFILE_SUCCESS;
}

int LoadSave::loadBinds(const std::string &path, KeyMap &p1, KeyMap &p2, KeyMap &p3, KeyMap &p4) const
{
  std::array<KeyMap, 4> keys;

  std::ifstream ifs(path);
  try {
    boost::archive::text_iarchive ia(ifs);
    ia >> keys;
  }
  catch ( const boost::archive::archive_exception & )
  {
	  p1 = { EKEY_CODE::KEY_KEY_W, EKEY_CODE::KEY_KEY_S, EKEY_CODE::KEY_KEY_A, EKEY_CODE::KEY_KEY_D, EKEY_CODE::KEY_LSHIFT };
	  p2 = { EKEY_CODE::KEY_UP, EKEY_CODE::KEY_DOWN, EKEY_CODE::KEY_LEFT, EKEY_CODE::KEY_RIGHT, EKEY_CODE::KEY_RSHIFT };
	  p3 = { EKEY_CODE::KEY_KEY_F, EKEY_CODE::KEY_KEY_C, EKEY_CODE::KEY_KEY_X, EKEY_CODE::KEY_KEY_V, EKEY_CODE::KEY_KEY_Z };
	  p4 = { EKEY_CODE::KEY_KEY_H, EKEY_CODE::KEY_KEY_N, EKEY_CODE::KEY_KEY_B, EKEY_CODE::KEY_KEY_M, EKEY_CODE::KEY_SPACE };
    return LOADFILE_NOACCESS;
  }

  auto k = OptionsScreen::KeyString.end();
  for (uint8_t i = 0; i < 4; i++)
  {
    if ((k = OptionsScreen::KeyString.find(keys[i].up)) == OptionsScreen::KeyString.end()
         || (k = OptionsScreen::KeyString.find(keys[i].down)) == OptionsScreen::KeyString.end()
         || (k = OptionsScreen::KeyString.find(keys[i].left)) == OptionsScreen::KeyString.end()
         || (k = OptionsScreen::KeyString.find(keys[i].right)) == OptionsScreen::KeyString.end()
         || (k = OptionsScreen::KeyString.find(keys[i].action)) == OptionsScreen::KeyString.end())
    {
      keys[0] = {EKEY_CODE::KEY_KEY_W, EKEY_CODE::KEY_KEY_S, EKEY_CODE::KEY_KEY_A, EKEY_CODE::KEY_KEY_D, EKEY_CODE::KEY_LSHIFT};
      keys[1] = {EKEY_CODE::KEY_UP, EKEY_CODE::KEY_DOWN, EKEY_CODE::KEY_LEFT, EKEY_CODE::KEY_RIGHT, EKEY_CODE::KEY_RSHIFT};
      keys[2] = {EKEY_CODE::KEY_KEY_F, EKEY_CODE::KEY_KEY_C, EKEY_CODE::KEY_KEY_X, EKEY_CODE::KEY_KEY_V, EKEY_CODE::KEY_KEY_Z};
      keys[3] = {EKEY_CODE::KEY_KEY_H, EKEY_CODE::KEY_KEY_N, EKEY_CODE::KEY_KEY_B, EKEY_CODE::KEY_KEY_M, EKEY_CODE::KEY_SPACE};
      break ;
    }
  }

  p1 = keys[0];
  p2 = keys[1];
  p3 = keys[2];
  p4 = keys[3];

  return LOADFILE_SUCCESS;
}

int LoadSave::saveFile(const std::string &path, const Settings &settings) const
{
  try {
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << settings;
  }
  catch ( const boost::archive::archive_exception & ) {
    std::function<void(std::string)> okFnc = &doNothing;
    Core::popUp.create(new Warning <std::string, std::string>(okFnc, okFnc, path, path));
    return LOADFILE_NOACCESS;
  }

  return LOADFILE_SUCCESS;
}

int LoadSave::serializeMap(const std::string &path, const Settings &settings) const
{
  try {
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << settings.mapSet;
  }
  catch ( const boost::archive::archive_exception & ) {
    std::cout << "Couldn't serialize" << std::endl;
    return LOADFILE_NOACCESS;
  }

  return LOADFILE_SUCCESS;
}

int LoadSave::saveScores(const std::string &path, const std::unordered_map<Indie::ScoreType, std::vector<std::pair<std::string, size_t>>, HashType<Indie::ScoreType>> &scoreMap) const
{
  try {
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << scoreMap;
  }
  catch ( const boost::archive::archive_exception & ) {
    return LOADFILE_NOACCESS;
  }

  return LOADFILE_SUCCESS;
}

int LoadSave::saveBinds(const std::string &path, const std::array<KeyMap, 4> &binds) const
{
  try {
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << binds;
  }
  catch ( const boost::archive::archive_exception & ) {
    return LOADFILE_NOACCESS;
  }

  return LOADFILE_SUCCESS;
}
