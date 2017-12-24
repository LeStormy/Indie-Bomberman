/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-16T12:40:08+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:12:05+02:00
 */

#include "IScreen.hpp"
#include "MenuScreens.hpp"
#include "Menu.hpp"
#include "Indie.hpp"
#include "Core.hpp"
#include "Loader.hpp"

#include "MenuEventReceiver.hpp"

bool Menu::FirstLaunch = true;
Indie::CurrentScreen Menu::currScreen = Indie::CurrentScreen::SPLASH;
bool Menu::reloadScreen = true;

Menu::Menu() : splashTimer(0.0f), switchSplash(true)
{

}

void Menu::init(Settings &settings)
{
  this->_allScreens[Indie::CurrentScreen::MAINPAGE] = std::make_unique<MainScreen>();
  this->_allScreens[Indie::CurrentScreen::OPTIONS] = std::make_unique<OptionsScreen>();
  this->_allScreens[Indie::CurrentScreen::SCOREBOARD] = std::make_unique<ScoreScreen>();
  this->_allScreens[Indie::CurrentScreen::SETGAME] = std::make_unique<SetGameScreen>();

  if (Menu::FirstLaunch == true)
  {
    LoadSave loader;
    this->DefaultSettings(settings);
    this->_allScreens[Indie::CurrentScreen::SPLASH] = std::make_unique<SplashScreen>();
    Menu::FirstLaunch = false;
    Menu::currScreen = Indie::CurrentScreen::SPLASH;
    Core::Sound.playMusic(AUDIO("SplashJingle"), false);
    this->splashTimer = std::chrono::duration<double>::zero();
    loader.loadBinds(CONF("/Binds.conf"), settings.players[0].keyMap, settings.players[1].keyMap, settings.players[2].keyMap, settings.players[3].keyMap);
  }
  else
  {
    Menu::currScreen = Indie::CurrentScreen::SETGAME;
    Core::Sound.stopAll();
    Core::Sound.playMusic(AUDIO("MenuMusic"));
  }
}

void Menu::ResetPlayers(Settings &sets, const std::pair<size_t, size_t> &mapSize)
{
  std::array<PlayerSet, 4> players;
  players[0] = {sets.players[0].playerType, sets.players[0].keyMap, 0.1f, sets.players[0].name, true, vector3df(1.5f, 0.0f, 1.5f), 1, 2, 1, 0, 0};
  players[1] = {sets.players[1].playerType, sets.players[1].keyMap, 0.1f, sets.players[1].name, true, vector3df(static_cast<float>(mapSize.first) - 1.5f, 0.0f, 1.5f), 1, 2, 1, 1, 0};
  players[2] = {sets.players[2].playerType, sets.players[2].keyMap, 0.1f, sets.players[2].name, true, vector3df(1.5f, 0.0f, static_cast<float>(mapSize.second) - 1.5f), 1, 2, 1, 2, 0};
  players[3] = {sets.players[3].playerType, sets.players[3].keyMap, 0.1f, sets.players[3].name, true, vector3df(static_cast<float>(mapSize.first) - 1.5f, 0.0f, static_cast<float>(mapSize.second) - 1.5f), 1, 2, 1, 3, 0};
  sets.players = players;
  for (uint16_t i = 0 ; i < sets.mapSet.newtiles.size(); i++)
    sets.mapSet.newtiles[i].push_back(Indie::GROUND_ENTITY);
  for (uint16_t i = 0 ; i < sets.mapSet.mapImage.map.size(); i++)
    sets.mapSet.mapImage.map[i] = 0;
  sets.hudSet.timer = 120;
  sets.hudSet.elapsed = std::chrono::duration<double>::zero();
}

void Menu::DefaultSettings(Settings &settings)
{
  MapSet mapSet;
  std::array<PlayerSet, 4> players;
  HUDSet hud;

  settings.players[0].playerType = Indie::HUMAN_PLAYER;
  settings.players[1].playerType = Indie::IA_PLAYER_EZ;
  settings.players[2].playerType = Indie::IA_PLAYER_EZ;
  settings.players[3].playerType = Indie::IA_PLAYER_EZ;
  settings.players[0].name = "Player 1";
  settings.players[1].name = "Player 2";
  settings.players[2].name = "Player 3";
  settings.players[3].name = "Player 4";

  mapSet.mapSize.first = 12;
  mapSet.mapSize.second = 12;
  for (uint16_t i = 0 ; i < mapSet.newtiles.size(); i++)
    mapSet.newtiles[i].push_back(Indie::GROUND_ENTITY);
  for (uint16_t i = 0 ; i < mapSet.mapImage.map.size(); i++)
    mapSet.mapImage.map[i] = 0;

  mapSet.blockDensity = 60;
  mapSet.floorDensity = 40;
  mapSet.platforms = true;
  mapSet.Biome = Indie::NEUTRAL;

  hud.timer = 120;
  hud.elapsed = std::chrono::duration<double>::zero();

  settings.mapSet = mapSet;
  settings.hudSet = hud;

  std::ifstream ifs(CONF("SoundSets.conf"));
  try {
    boost::archive::text_iarchive ia(ifs);
    ia >> Core::Sound.Sets;
  }
  catch ( const boost::archive::archive_exception & ) {
    Core::Sound.Sets = {100, 100, 100, false};
  }
}

void Menu::update(Settings &settings)
{
  if (splashTimer == std::chrono::duration<double>::zero())
    this->startTime = std::chrono::system_clock::now();
  if (Menu::currScreen == Indie::SPLASH && splashTimer.count() >= 8 && switchSplash == true)
  {
    Menu::currScreen = Indie::MAINPAGE;
    Menu::reloadScreen = true;
    Core::Sound.stopAll();
    Core::Sound.playMusic(AUDIO("MenuMusic"));
    switchSplash = false;
  }
  else if (Menu::currScreen == Indie::SPLASH)
    this->splashTimer = Core::Time - this->startTime;
  if (Menu::reloadScreen == true)
  {
    Menu::reloadScreen = false;
    Core::Display.env->clear();
    this->_allScreens[Menu::currScreen]->sceneSetter(settings);
  }
}
