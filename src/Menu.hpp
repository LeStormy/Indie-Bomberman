/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-16T11:33:50+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:11:56+02:00
 */

#ifndef MENU_HPP_
# define MENU_HPP_

#include <memory>
#include <unordered_map>
#include <iostream>
#include <irrlicht/irrlicht.h>
#include "Indie.hpp"
#include "IScreen.hpp"
#include "PlayersManager.hpp"
#include "HashType.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class IScreen;

class Menu {
public:
  Menu();
  ~Menu() {}

  void init(Settings &settings);
  void update(Settings &settings);
  static void DefaultSettings(Settings &settings);
  static void ResetPlayers(Settings &sets, const std::pair<size_t, size_t> &mapSize);

public:

  static bool FirstLaunch;
  static Indie::CurrentScreen currScreen;
  static bool reloadScreen;

private:
  std::unordered_map<Indie::CurrentScreen, std::unique_ptr<IScreen>, HashType<Indie::CurrentScreen>> _allScreens;
  std::chrono::time_point<std::chrono::system_clock> startTime;
  std::chrono::duration<double> splashTimer;
  bool switchSplash;
};

#endif
