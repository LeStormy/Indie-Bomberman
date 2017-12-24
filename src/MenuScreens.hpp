/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-16T11:02:14+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:58:38+02:00
 */

#ifndef MENUSCREENS_HPP_
# define MENUSCREENS_HPP_

#include <vector>
#include <map>
#include <unordered_map>
#include <irrlicht/irrlicht.h>
#include <memory>
#include "IScreen.hpp"
#include "Indie.hpp"
#include "Core.hpp"
#include "Directory.hpp"
#include "Menu.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

# define X(Index) static_cast<s32>((Index)*(Core::Resolution.Width / 20))
# define Y(Index) static_cast<s32>((Index)*(Core::Resolution.Height / 10))

class Button {
public:
  template <typename T>
  Button(const io::path &bTex, const io::path &bTexPressed,
         const rect<s32> &bPos, T bType, bool visibility = true) {
    ITexture *btex1 = Core::Display.driver->getTexture(bTex);
    ITexture *btex1Pressed = Core::Display.driver->getTexture(bTexPressed);

    IGUIButton *mybutton1 = Core::Display.env->addButton(bPos, 0, bType);

    mybutton1->setImage(btex1);
    mybutton1->setPressedImage(btex1Pressed);
    mybutton1->setUseAlphaChannel(true);
    mybutton1->setVisible(visibility);
    mybutton1->setScaleImage(true);
    mybutton1->setDrawBorder(0);
    this->mybutton = mybutton1;
  }
  ~Button() {}

private:
  IGUIButton *mybutton;
};

class SplashScreen : public IScreen {
public:
  SplashScreen();
  ~SplashScreen() {}
  void sceneSetter(const Settings &settings);

private:
};

////////

class MainScreen : public IScreen {
public:
  MainScreen() {}
  ~MainScreen() {}
  void sceneSetter(const Settings &settings);

private:
};

////////

class ScoreScreen : public IScreen {
public:
	ScoreScreen();
	~ScoreScreen() {}

	void sceneSetter(const Settings &);
private:
	std::unordered_map<Indie::ScoreType,
		std::vector<std::pair<std::string, size_t>>,
		HashType<Indie::ScoreType>> _allScores;
};

////////

class OptionsScreen : public IScreen {
public:
  OptionsScreen();
  ~OptionsScreen() {}
  void sceneSetter(const Settings &settings);

  static int currPlayer;
  static SoundSets SoundSettings;
  static short s_to_map;

  static std::unordered_map<irr::EKEY_CODE, std::string, HashType<irr::EKEY_CODE>> KeyString;

private:
  std::vector<std::string> _players;
};

////////

class SetGameScreen : public IScreen {
public:
  SetGameScreen();
  ~SetGameScreen() {}

  void setPlayers(const Settings &);
  void setMap(const Settings &);
  void setCustom(const Settings &);
  void setPremade(const Settings &);

  void  sceneSetter(const Settings &settings);


  static bool customMap;
  static int8_t premadeSize;
  static int8_t premadeIndex;
  static char isChangingName;
private:
  std::vector<std::string> MapPreview;

};

#endif
