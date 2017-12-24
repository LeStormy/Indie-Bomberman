/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-25T11:11:54+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T22:27:09+02:00
 */

#include <thread>
#include <mutex>
#include "Core.hpp"
#include "HudSet.hpp"
#include "ScreenShot.hpp"

#define ABS(v) (v) > 0 ? (v) : (-v)

Hud::Hud() : startTimer(true), counting(false), _hurry(Text("Hurry Up !", rect<s32>(0,0,1920,1080), 150)), saved(false), remHurry(true)
{
  this->timerFont = CGUITTFont::createTTFont(Core::Display.env, MISC("Font.ttf"), 70);
  this->hurryFont = CGUITTFont::createTTFont(Core::Display.env, MISC("FontBig.ttf"), 150);
  _hurry.guiTxt->setVisible(false);

  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(70,260,120,310)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb1")));
  _powerUps[0].back()->setScaleImage(true);
  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(200,260,250,310)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb2")));
  _powerUps[0].back()->setScaleImage(true);
  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(260,260,310,310)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedPlus")));
  _powerUps[0].back()->setVisible(false);
  _powerUps[0].back()->setScaleImage(true);
  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(260,260,310,310)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedLess")));
  _powerUps[0].back()->setVisible(false);
  _powerUps[0].back()->setScaleImage(true);
  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(10,320,60,370)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("Invincible")));
  _powerUps[0].back()->setVisible(false);
  _powerUps[0].back()->setScaleImage(true);
  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(70,320,120,370)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("KickBonus")));
  _powerUps[0].back()->setVisible(false);
  _powerUps[0].back()->setScaleImage(true);
  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(140,320,190,370)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("IceBonus")));
  _powerUps[0].back()->setVisible(false);
  _powerUps[0].back()->setScaleImage(true);
  _powerUps[0].push_back(Core::Display.env->addImage(rect<s32>(200,320,250,370)));
  _powerUps[0].back()->setImage(Core::Display.driver->getTexture(IMAGE("OilBonus")));
  _powerUps[0].back()->setVisible(false);
  _powerUps[0].back()->setScaleImage(true);

  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(70,610,120,660)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb1")));
  _powerUps[1].back()->setScaleImage(true);
  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(200,610,250,660)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb2")));
  _powerUps[1].back()->setScaleImage(true);
  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(260,610,310,660)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedPlus")));
  _powerUps[1].back()->setVisible(false);
  _powerUps[1].back()->setScaleImage(true);
  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(260,610,310,660)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedLess")));
  _powerUps[1].back()->setVisible(false);
  _powerUps[1].back()->setScaleImage(true);
  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(10,670,60,720)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("Invincible")));
  _powerUps[1].back()->setVisible(false);
  _powerUps[1].back()->setScaleImage(true);
  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(70,670,120,720)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("KickBonus")));
  _powerUps[1].back()->setVisible(false);
  _powerUps[1].back()->setScaleImage(true);
  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(140,670,190,720)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("IceBonus")));
  _powerUps[1].back()->setVisible(false);
  _powerUps[1].back()->setScaleImage(true);
  _powerUps[1].push_back(Core::Display.env->addImage(rect<s32>(200,670,250,720)));
  _powerUps[1].back()->setImage(Core::Display.driver->getTexture(IMAGE("OilBonus")));
  _powerUps[1].back()->setVisible(false);
  _powerUps[1].back()->setScaleImage(true);

  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1670,260,1720,310)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb1")));
  _powerUps[2].back()->setScaleImage(true);
  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1800,260,1850,310)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb2")));
  _powerUps[2].back()->setScaleImage(true);
  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1860,260,1910,310)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedPlus")));
  _powerUps[2].back()->setVisible(false);
  _powerUps[2].back()->setScaleImage(true);
  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1860,260,1910,310)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedLess")));
  _powerUps[2].back()->setVisible(false);
  _powerUps[2].back()->setScaleImage(true);
  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1610,320,1660,370)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("Invincible")));
  _powerUps[2].back()->setVisible(false);
  _powerUps[2].back()->setScaleImage(true);
  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1670,320,1720,370)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("KickBonus")));
  _powerUps[2].back()->setVisible(false);
  _powerUps[2].back()->setScaleImage(true);
  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1740,320,1790,370)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("IceBonus")));
  _powerUps[2].back()->setVisible(false);
  _powerUps[2].back()->setScaleImage(true);
  _powerUps[2].push_back(Core::Display.env->addImage(rect<s32>(1800,320,1850,370)));
  _powerUps[2].back()->setImage(Core::Display.driver->getTexture(IMAGE("OilBonus")));
  _powerUps[2].back()->setVisible(false);
  _powerUps[2].back()->setScaleImage(true);

  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1670,610,1720,660)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb1")));
  _powerUps[3].back()->setScaleImage(true);
  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1800,610,1850,660)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("hudNb2")));
  _powerUps[3].back()->setScaleImage(true);
  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1860,610,1910,660)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedPlus")));
  _powerUps[3].back()->setVisible(false);
  _powerUps[3].back()->setScaleImage(true);
  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1860,610,1910,660)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("SpeedLess")));
  _powerUps[3].back()->setVisible(false);
  _powerUps[3].back()->setScaleImage(true);
  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1610,670,1660,720)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("Invincible")));
  _powerUps[3].back()->setVisible(false);
  _powerUps[3].back()->setScaleImage(true);
  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1670,670,1720,720)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("KickBonus")));
  _powerUps[3].back()->setVisible(false);
  _powerUps[3].back()->setScaleImage(true);
  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1740,670,1790,720)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("IceBonus")));
  _powerUps[3].back()->setVisible(false);
  _powerUps[3].back()->setScaleImage(true);
  _powerUps[3].push_back(Core::Display.env->addImage(rect<s32>(1800,670,1850,720)));
  _powerUps[3].back()->setImage(Core::Display.driver->getTexture(IMAGE("OilBonus")));
  _powerUps[3].back()->setVisible(false);
  _powerUps[3].back()->setScaleImage(true);

  for (uint8_t i = 0; i < 4; i++)
  {
    _ranges[i] = 2;
    _counts[i] = 1;
  }
}

Hud::~Hud()
{
  if (this->timerFont)
    this->timerFont->drop();
  if (this->hurryFont)
    this->hurryFont->drop();
}

void Hud::init(const Settings &sets)
{
  ITexture *image = Core::Display.driver->getTexture(IMAGE("HudP1"));
  Core::Display.env->addImage(image, position2d<int>(0,50));
  Text(sets.players[0].name, rect<s32>(0,50,300,100), 40);
  Dead[0] = Core::Display.env->addImage(rect<s32>(0,50, 300, 250));
  Dead[0]->setImage(Core::Display.driver->getTexture(IMAGE("Dead")));
  Dead[0]->setVisible(false);

  image = Core::Display.driver->getTexture(IMAGE("HudP2"));
  Core::Display.env->addImage(image, position2d<int>(0,400));
  Text(sets.players[1].name, rect<s32>(0,400,300,450), 40);
  Dead[1] = Core::Display.env->addImage(rect<s32>(0,400, 300, 600));
  Dead[1]->setImage(Core::Display.driver->getTexture(IMAGE("Dead")));
  Dead[1]->setVisible(false);

  image = Core::Display.driver->getTexture(IMAGE("HudP3"));
  Core::Display.env->addImage(image, position2d<int>(1590,50));
  Text(sets.players[2].name, rect<s32>(1620,50,1920,100), 40);
  Dead[2] = Core::Display.env->addImage(rect<s32>(1620,50, 1920, 250));
  Dead[2]->setImage(Core::Display.driver->getTexture(IMAGE("Dead")));
  Dead[2]->setVisible(false);

  image = Core::Display.driver->getTexture(IMAGE("HudP4"));
  Core::Display.env->addImage(image, position2d<int>(1590,400));
  Text(sets.players[3].name, rect<s32>(1620,400,1920,450), 40);
  Dead[3] = Core::Display.env->addImage(rect<s32>(1620,400, 1920, 600));
  Dead[3]->setImage(Core::Display.driver->getTexture(IMAGE("Dead")));
  Dead[3]->setVisible(false);


  image = Core::Display.driver->getTexture(IMAGE("HudTimer"));
  Core::Display.env->addImage(image, position2d<int>(810,0));

  IGUIImage *PUImage = Core::Display.env->addImage(rect<s32>(10,260,60,310));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Bombs")));
  PUImage->setScaleImage(true);
  PUImage = Core::Display.env->addImage(rect<s32>(10,610,60,660));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Bombs")));
  PUImage->setScaleImage(true);
  PUImage = Core::Display.env->addImage(rect<s32>(1610,260,1660,310));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Bombs")));
  PUImage->setScaleImage(true);
  PUImage = Core::Display.env->addImage(rect<s32>(1610,610,1660,660));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Bombs")));
  PUImage->setScaleImage(true);

  PUImage = Core::Display.env->addImage(rect<s32>(140,260,190,310));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Power")));
  PUImage->setScaleImage(true);
  PUImage = Core::Display.env->addImage(rect<s32>(140,610,190,660));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Power")));
  PUImage->setScaleImage(true);
  PUImage = Core::Display.env->addImage(rect<s32>(1740,260,1790,310));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Power")));
  PUImage->setScaleImage(true);
  PUImage = Core::Display.env->addImage(rect<s32>(1740,610,1790,660));
  PUImage->setImage(Core::Display.driver->getTexture(IMAGE("Power")));
  PUImage->setScaleImage(true);

  _start = std::chrono::system_clock::now();
  _start -= sets.hudSet.elapsed;
  this->path << Core::AssetsDir << "/Misc/Maps/map" << Core::Display.device->getTimer()->getRealTime();
  this->scr = std::make_unique<ScreenShot>(path.str());
}

void Hud::autoSave(const Settings & settings)
{
  this->path << ".map";
  loader.serializeMap(path.str(), settings);
  this->saved = true;
}

void Hud::clearBonus()
{
  for (int i = 0; i < 4; i++)
    for (int j = 4; j < 8; j++)
      _powerUps[i].at(j)->setVisible(false);
}

void Hud::displayBonus(uint16_t range, uint16_t count, size_t player)
{
  if (count != this->_counts[player])
  {
    _powerUps[player].at(0)->setImage(Core::Display.driver->getTexture(IMAGE("hudNb" + std::to_string(count))));
    this->_counts[player] = count;
  }
  if (range != this->_ranges[player])
  {
    _powerUps[player].at(1)->setImage(Core::Display.driver->getTexture(IMAGE("hudNb" + std::to_string(range))));
    this->_ranges[player] = range;
  }
}

void Hud::displayBonus(Indie::BombType bType, size_t player)
{
  switch (bType)
  {
    case Indie::FROZEN_BOMB :
      _powerUps[player].at(6)->setVisible(true);
      break ;
    case Indie::OIL_BOMB :
      _powerUps[player].at(7)->setVisible(true);
      break ;
    default :;

  }
}

void Hud::displayBonus(Indie::EffectType eType, float speed, size_t player)
{
  switch (eType)
  {
    case Indie::SPEED_EFFECT :
    {
      if (speed > 1)
      {
        _powerUps[player].at(2)->setVisible(true);
        _powerUps[player].at(3)->setVisible(false);
      }
      else if (speed < 1)
      {
        _powerUps[player].at(2)->setVisible(false);
        _powerUps[player].at(3)->setVisible(true);
      }
      else
      {
        _powerUps[player].at(2)->setVisible(false);
        _powerUps[player].at(3)->setVisible(false);
      }
      break ;
    }
    case Indie::INVINCIBLE_EFFECT :
      _powerUps[player].at(4)->setVisible(true);
      break ;
    case Indie::KICK_EFFECT :
      _powerUps[player].at(5)->setVisible(true);
      break ;
    default :;
  }
}

void Hud::updatePU(const std::array<std::unique_ptr<APlayer>, 4> *players, const Settings &sets)
{
  this->clearBonus();
  for (size_t i = 0; i < 4; i++)
  {
    if (players->at(i) == nullptr
        || sets.players[i].playerType == Indie::UNUSED_PLAYER
        || sets.players[i].alive == false)
      {
        Dead[i]->setVisible(true);
        continue ;
      }
    this->displayBonus(players->at(i)->getBombRange(),players->at(i)->getBombCount() , i);
    if (players->at(i)->getBombType() != Indie::CLASSIC_BOMB)
      this->displayBonus(players->at(i)->getBombType(), i);
    for (size_t j = 2; j < static_cast<int>(Indie::EffectType::EFFECT_COUNT); j++)
      if (players->at(i)->hasBonus(static_cast<Indie::EffectType>(j)))
        this->displayBonus(static_cast<Indie::EffectType>(j), players->at(i)->getRealSpeed(), i);
  }
}

void Hud::removeHurry()
{
  if (remHurry == true)
  {
    this->_hurry.guiTxt->remove();
    remHurry = false;
  }
}

bool Hud::Save = false;

void Hud::update(Settings &sets, const std::array<std::unique_ptr<APlayer>, 4> *players)
{
  std::chrono::duration<double>	elap;
  elap = std::chrono::system_clock::now() - _start;
  updatePU(players, sets);
  if (saved == true && Hud::Save == true)
    Hud::Save = false;
  if (Hud::Save == true)
  {
    std::thread *saveThread = new std::thread(&Hud::autoSave, this, sets);
    static_cast<void>(saveThread);
    Hud::Save = false;
    scr->takeScreenshot();
  }
  if ((elap != sets.hudSet.elapsed || startTimer == true) && counting == true)
  {
    if (!startTimer)
      _timer->remove();
    startTimer = false;
    if (sets.hudSet.timer - sets.hudSet.elapsed.count() >= 0)
    {
      uint64_t min = std::chrono::seconds(sets.hudSet.timer - static_cast<uint64_t>(sets.hudSet.elapsed.count())).count() / 60;
      uint64_t sec = std::chrono::seconds(sets.hudSet.timer - static_cast<uint64_t>(sets.hudSet.elapsed.count())).count() % 60;
      std::string counter("");
      if (min / 60 < 10)
        counter += "0";
      counter += std::to_string(min) + ":";
      if (sec % 60 < 10)
        counter += "0";
      counter += std::to_string(sec);

      std::wstring save(counter.begin(), counter.end());
      this->_timer = Core::Display.env->addStaticText(save.c_str(), rect<s32>(810,0,1110,150));
    }
    else
      this->_timer = Core::Display.env->addStaticText(L"00:00", rect<s32>(810,0,1110,150));
    _timer->setOverrideFont(this->timerFont);
    if (static_cast<int>(sets.hudSet.timer - sets.hudSet.elapsed.count()) >= 0
        || (sets.hudSet.timer - static_cast<int>(sets.hudSet.elapsed.count())) % 2 == 0)
      _timer->setOverrideColor(SColor(255, 255, 255, 255));
    else
      _timer->setOverrideColor(SColor(255, 255, 0, 0));
    if (static_cast<int>(sets.hudSet.timer - sets.hudSet.elapsed.count()) < 35
        && static_cast<int>(sets.hudSet.timer - sets.hudSet.elapsed.count()) > 30)
    {
      this->_hurry.guiTxt->setVisible(true);
      this->_hurry.guiTxt->setOverrideFont(this->hurryFont);
      this->_hurry.guiTxt->setOverrideColor(SColor(static_cast<int>(((sets.hudSet.elapsed.count() - sets.hudSet.timer) * 100)) %127,
                                                                      static_cast<int>(((sets.hudSet.elapsed.count() - sets.hudSet.timer) * 100)) % 127 + 127,
                                                                      0,0));
    }
    if (static_cast<int>(sets.hudSet.timer - sets.hudSet.elapsed.count()) <= 30 && remHurry)
    {
      this->_hurry.guiTxt->remove();
      remHurry = false;
    }
    _timer->setTextRestrainedInside(false);
    _timer->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
    sets.hudSet.elapsed = elap;
  }
}
