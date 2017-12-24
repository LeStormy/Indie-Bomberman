/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-16T20:19:43+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-17T16:27:49+02:00
 */

#ifndef CORE_HPP
# define CORE_HPP

#include <memory>
#include "Indie.hpp"
#include "DisplayEngine.hpp"
#include "SoundEngine.hpp"
#include "Menu.hpp"
#include "MapHandler.hpp"
#include "MenuEventReceiver.hpp"
#include "PauseEventReceiver.hpp"
#include "HudSet.hpp"
#include "Tile.hpp"
#include "APlayer.hpp"
#include "InGameMenu.hpp"
#include "IScreen.hpp"
#include "GameOver.hpp"
#include "StartGame.hpp"

# define IMAGE(V) (Core::AssetsDir + "/Media/Images/" + (V) + ".png").c_str()
# define MESH(V) (Core::AssetsDir + "/Media/Mesh/" + (V)).c_str()
# define MESHTXT(V) (Core::AssetsDir + "/Media/Images/Mesh/" + (V)).c_str()
# define AUDIO(V) (Core::AssetsDir + "/Media/Audio/" + (V) + ".ogg").c_str()
# define MISC(V) (Core::AssetsDir + "/Media/Misc/" + (V)).c_str()
# define CONF(V) (Core::AssetsDir + "/Misc/" + (V)).c_str()
# define RAD(V) (V) * M_PI / 180

class PopUpManager;

class Core
{
  public:
    Core();
    ~Core()
    {
      _mReceiver.reset(nullptr);
      _input.reset(nullptr);
      _pmng.reset(nullptr);
      _mhdl.reset(nullptr);
      _hud.reset(nullptr);
      Display.freeAll();
    }

    static dimension2d<u32> Resolution;
    static DisplayEngine Display;
    static SoundEngine Sound;
    static PopUpManager popUp;
    static float        frameRate;
    static float        speedRatio;
    static std::string AssetsDir;
    static std::chrono::time_point<std::chrono::system_clock> Time;

    void run(void);

  private:
    template <Indie::DisplayInstance T>
    void  update() {}

    template <Indie::SwitchDisplay T>
    void  DisplaySwitch() {}

    void ChangeDisplay(Indie::SwitchDisplay);

    void updateFR(void);
    inline void setDisplayMode(Indie::DisplayInstance disMode) { DisplayEngine::dInstance = disMode; }

  private:
    std::unique_ptr<Menu>           	_menu;
    std::unique_ptr<StartGame>       _gameIntro;
    std::unique_ptr<InGameMenu>       _igMenu;
    Settings                        	_sets;
    std::unique_ptr<MenuEventReceiver> 	_mReceiver;
    std::unique_ptr<PauseEventReceiver> _pReceiver;
    std::unique_ptr<Input>          	_input;
    std::unique_ptr<PlayersManager> 	_pmng;
    std::unique_ptr<MapHandler>     	_mhdl;
    std::unique_ptr<Hud>            	_hud;
    std::unique_ptr<GameOver>          	_gameOver;
    std::unique_ptr<IScreen>    	_opts;
//  Indie::DISPLAY_INSTANCE         _disMode;

  bool gameStart;

    std::chrono::time_point<std::chrono::system_clock> _end;

};

#endif
