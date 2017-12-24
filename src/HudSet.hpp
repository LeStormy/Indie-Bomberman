/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-25T11:12:05+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:36:34+02:00
 */

#ifndef HUDSET_HPP
# define HUDSET_HPP

#include <sstream>
#include <memory>
#include "Settings.hpp"
#include "Text.hpp"
#include "Loader.hpp"
#include "CGUITTFont.h"
#include "ScreenShot.hpp"

class Hud {
public:
  Hud();
  ~Hud();

  void update(Settings &sets, const std::array<std::unique_ptr<APlayer>, 4> *players);
  void init(const Settings &sets);
  void updatePU(const std::array<std::unique_ptr<APlayer>, 4> *players, const Settings &sets);
  void autoSave(const Settings &sets);
  void removeHurry();

  bool startTimer;
  bool counting;

static bool Save;

private:
  void displayBonus(uint16_t range, uint16_t count, size_t player);
  void displayBonus(Indie::BombType bType, size_t player);
  void displayBonus(Indie::EffectType eType, float speed, size_t player);
  void clearBonus();

  std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>>	_start;
  IGUIStaticText *_timer;
  Text _hurry;
  CGUITTFont *timerFont;
  CGUITTFont *hurryFont;
  LoadSave loader;
  std::array<std::vector<IGUIImage *>, 4> _powerUps;
  std::array<uint16_t, 4> _ranges;
  std::array<uint16_t, 4> _counts;
  std::ostringstream path;
  bool saved;
  std::unique_ptr<ScreenShot> scr;
  bool remHurry;
  std::array<IGUIImage *, 4> Dead;
};

#endif
