/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-16T20:29:03+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:57:42+02:00
 */

#include "Core.hpp"
#include "ProceduralGeneration.hpp"
#include "MenuScreens.hpp"
#include "APlayer.hpp"
#include "ErrorMessage.hpp"
#include "MeshPathGetter.hpp"
#include "Warning.hpp"

DisplayEngine Core::Display;
SoundEngine Core::Sound;
dimension2d<u32> Core::Resolution = {0, 0};
PopUpManager Core::popUp;
float Core::frameRate = 0.016f;
float Core::speedRatio = 1.0f;
std::string Core::AssetsDir = "";
std::chrono::time_point<std::chrono::system_clock> Core::Time = std::chrono::system_clock::now();

Core::Core() {
  Core::Display.initAll();
}


template<>
void  Core::update<Indie::DisplayInstance::MENU>()
{
  _menu->update(this->_sets);
  Display.camera.Update(std::pair<size_t, size_t>(2,2));
}

template<>
void  Core::update<Indie::DisplayInstance::START_GAME>()
{
  _gameIntro->update();
  Display.camera.Update(_sets.mapSet.mapSize);
}

template<>
void  Core::update<Indie::DisplayInstance::GAME>()
{
  _mhdl->update();
  _pmng->update();
  _hud->update(this->_sets, _pmng->getPlayers());
  if (_gameOver->isEnd(this->_sets.players) == true)
    DisplayEngine::dSwitch = Indie::TO_END;
  Display.camera.Update(_sets.mapSet.mapSize);

}

template<>
void  Core::update<Indie::DisplayInstance::GAME_PAUSED>()
{
  _hud->update(this->_sets, _pmng->getPlayers());
}

template<>
void  Core::update<Indie::DisplayInstance::IG_SETS>()
{
  if (Menu::reloadScreen)
  {
    _opts->sceneSetter(_sets);
    Menu::reloadScreen = false;
  }
}

template<>
void  Core::update<Indie::DisplayInstance::END_GAME>()
{
  _mhdl->update();
  _gameOver->update();
  Display.camera.Update(_sets.mapSet.mapSize);
}

template <>
void Core::DisplaySwitch<Indie::TO_MENU>()
{
  if (Display.smgr) {
    this->_hud.reset(nullptr);
    this->_mhdl.reset(nullptr);
    this->_pmng.reset(nullptr);
    Display.smgr->clear();
    Display.env->clear();
  }
  SAppContext context;
  context.device = Core::Display.device;
  context.settings = &this->_sets;
  _mReceiver = std::make_unique<MenuEventReceiver>(context);
  Core::Display.device->setEventReceiver(_mReceiver.get());
  this->_menu = std::make_unique<Menu>();
  this->_menu->init(this->_sets);
  Menu::reloadScreen = true;
  Display.camera.InitCam(std::pair<size_t, size_t>(0,0), true);
  Display.camera.SplashZoom(4.0);
  setDisplayMode(Indie::MENU);
}

void OkFnc(bool ok)
{
  Core::Display.smgr->clear();
  Core::Display.env->clear();
  DisplayEngine::dSwitch = Indie::TO_MENU;
  DisplayEngine::dInstance = Indie::MENU;
  (void)ok;
}

template <>
void Core::DisplaySwitch<Indie::TO_START_GAME>()
{
  _opts.reset(nullptr);

  Core::Display.light.clear();
  _mhdl.reset(nullptr);
  _pmng.reset(nullptr);

  Core::Display.smgr->clear();
  Core::Display.env->clear();


  Core::Display.driver->beginScene(true, true, SColor(255, 0, 0, 0));
  Core::Display.env->drawAll();
  Core::Display.driver->endScene();



    ITexture* img = Core::Display.driver->getTexture(IMAGE("DarkFilter"));
    Core::Display.env->addImage(img, position2d<int>(0,0));
    Text txt("Loading...", rect<s32>(0,0,1920,1080), 150);
    Core::Sound.playMusic(AUDIO("LoadMusic"));
    Core::Display.driver->beginScene(true, true, SColor(255, 0, 0, 0));
    Core::Display.env->drawAll();
    Core::Display.driver->endScene();


    IAnimatedMeshSceneNode *node;
    ITexture *texture;
    bool failure = false;
    texture = Core::Display.driver->getTexture(IMAGE("1"));
    texture = Core::Display.driver->getTexture(IMAGE("2"));
    texture = Core::Display.driver->getTexture(IMAGE("3"));
    texture = Core::Display.driver->getTexture(IMAGE("Go"));
    texture = Core::Display.driver->getTexture(IMAGE("HudTimer"));
    texture = Core::Display.driver->getTexture(IMAGE("HudP1"));
    texture = Core::Display.driver->getTexture(IMAGE("HudP2"));
    texture = Core::Display.driver->getTexture(IMAGE("HudP3"));
    texture = Core::Display.driver->getTexture(IMAGE("HudP4"));
    texture = Core::Display.driver->getTexture(IMAGE("hudNb1"));
    texture = Core::Display.driver->getTexture(IMAGE("hudNb2"));
    texture = Core::Display.driver->getTexture(IMAGE("SpeedPlus"));
    texture = Core::Display.driver->getTexture(IMAGE("SpeedLess"));
    texture = Core::Display.driver->getTexture(IMAGE("Invincible"));
    texture = Core::Display.driver->getTexture(IMAGE("KickBonus"));
    texture = Core::Display.driver->getTexture(IMAGE("IceBonus"));
    texture = Core::Display.driver->getTexture(IMAGE("OilBonus"));
    texture = Core::Display.driver->getTexture(IMAGE("Bombs"));
    texture = Core::Display.driver->getTexture(IMAGE("Power"));
    for (size_t i = 0; i < static_cast<int>(Indie::Entity::VOID_ENTITY); ++i)
    {
      if (!(node = Core::Display.smgr->addAnimatedMeshSceneNode(Core::Display.smgr->getMesh(MeshPathFromEnum::getMeshPath(static_cast<Indie::Entity>(i)))))
          || !(texture = Core::Display.driver->getTexture(MeshPathFromEnum::getTexturePath(static_cast<Indie::Entity>(i)))))
      {
        failure = true;
        break ;
      }
      node->setMaterialTexture(0, texture);
      node->remove();
      Core::Display.driver->beginScene(true, true, SColor(255, 0, 0, 0));
      Core::Display.smgr->drawAll();
      Core::Display.env->drawAll();
      Core::Display.driver->endScene();
    }

    if (failure == true)
    {
      std::function<void(bool)> ok = &OkFnc;
      Core::popUp.create(new Warning<bool, bool>(ok,ok, false, false, "Fatal Error !\nMissing Texture Files !", true, false));
      DisplayEngine::dInstance = static_cast<Indie::DisplayInstance>(-1);
      return ;
    }

    Core::Display.smgr->clear();


  setDisplayMode(Indie::START_GAME);

  scene::ISceneNode* skydome= Core::Display.smgr->addSkyDomeSceneNode(Core::Display.driver->getTexture(IMAGE("skydome_blue")),16,8,0.95f,2.0f);
  skydome = skydome;

  Menu::ResetPlayers(_sets, _sets.mapSet.mapSize);

  _menu.reset(nullptr);
  _igMenu.reset(nullptr);
  _gameOver.reset(new GameOver);

  _sets.hudSet.gameDate = std::chrono::system_clock::now();

  _input = std::make_unique<Input>(std::array<KeyMap, 4>{_sets.players[0].keyMap, _sets.players[1].keyMap, _sets.players[2].keyMap, _sets.players[3].keyMap});

  if (SetGameScreen::customMap)
  {
    ProceduralGeneration pg(_sets.mapSet);
    pg.generateMap();
  }

    _mhdl.reset(new MapHandler(_sets.mapSet, &_sets.hudSet, &_sets.players));
    _pmng.reset(new PlayersManager(&_sets.players, this->_mhdl.get(), this->_input.get()));
    Display.camera.InitCam(_sets.mapSet.mapSize);

  Core::Display.light.init();
  Core::Display.light.setMapAffectedSize(_sets.mapSet.mapSize);

  Core::Display.light.lightOnScene();

  Core::Display.env->clear();

  Core::Display.driver->beginScene(true, true, SColor(255, 0, 0, 0));
  Core::Display.smgr->drawAll();
  Core::Display.env->drawAll();
  Core::Display.driver->endScene();

  _gameIntro = std::make_unique<StartGame>();

  _gameIntro->startTimer();
  Display.camera.AroundTheWorld(4.0, _sets.mapSet.mapSize);

  }

  template <>
  void Core::DisplaySwitch<Indie::TO_GAME>()
  {
    Display.env->clear();

    _gameIntro.reset(nullptr);

    Display.camera.PlaceGameCamera();

    _hud.reset(new Hud());
    _hud->counting = true;
    _hud->startTimer = true;
    setDisplayMode(Indie::GAME);

    if (Core::Sound.MainAudio.getStatus() != sf::SoundSource::Playing)
    {
      Core::Sound.playMusic(AUDIO("InGameMusic"));
    }

    Core::Display.device->setEventReceiver(_input.get());
    gameStart = true;
    _hud->counting = true;
    _hud->startTimer = true;
    _hud->init(this->_sets);

  }

  template <>
  void Core::DisplaySwitch<Indie::TO_GAME_PAUSED>()
  {
    _hud->counting = false;
    if (DisplayEngine::dInstance == Indie::IG_SETS)
    {
      _pReceiver.reset(nullptr);
      _input->changeKeys(std::array<KeyMap, 4>{_sets.players[0].keyMap, _sets.players[1].keyMap, _sets.players[2].keyMap, _sets.players[3].keyMap});
      Core::Display.device->setEventReceiver(_input.get());
      Core::Display.env->clear();
      _hud.reset(new Hud());
      _hud->init(this->_sets);
    }
    _igMenu = std::make_unique<InGameMenu>();
    setDisplayMode(Indie::GAME_PAUSED);
  }

  template <>
  void Core::DisplaySwitch<Indie::TO_IG_SETS>()
  {
     SAppContext context;
    context.device = Core::Display.device;
    context.settings = &this->_sets;
    _pReceiver = std::make_unique<PauseEventReceiver>(context);
    Core::Display.device->setEventReceiver(_pReceiver.get());
    setDisplayMode(Indie::IG_SETS);
    _opts.reset(new OptionsScreen);
    _opts->sceneSetter(_sets);
  }

  template <>
  void Core::DisplaySwitch<Indie::TO_END>()
  {
    setDisplayMode(Indie::END_GAME);
    _hud->removeHurry();
    Core::Sound.playMusic(AUDIO("EndJingle"), false);
    _gameOver->setWinner(_sets.players);
    _gameOver->startTimer();
    Core::Display.device->setEventReceiver(_mReceiver.get());
    if (_gameOver->getWinner() != 0)
    {
      Core::Display.light.lightOnScene(false);
      switch (_pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getDirection())
      {
        case Indie::DOWN_DIRECTION :
          Core::Display.light.addSpotLight(vector3df(_pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().X,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Y + 3,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Z - 2),
                                           1.0f, 20.0f, 1.0f, SColorf(1,1,1,1),SColorf(1,1,1,1),SColorf(1,1,1,1), vector3df(40, 0, 0));
          break;
        case Indie::UP_DIRECTION :
          Core::Display.light.addSpotLight(vector3df(_pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().X,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Y + 3,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Z + 2),
                                           1.0f, 20.0f, 1.0f, SColorf(1,1,1,1),SColorf(1,1,1,1),SColorf(1,1,1,1), vector3df(140, 0, 0));
          break;
        case Indie::LEFT_DIRECTION :
          Core::Display.light.addSpotLight(vector3df(_pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().X - 2.5F,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Y + 3.5f,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Z),
                                           1.0f, 20.0f, 1.0f, SColorf(1,1,1,1),SColorf(1,1,1,1),SColorf(1,1,1,1), vector3df(80, 90, 40));
          break;
        case Indie::RIGHT_DIRECTION :
          Core::Display.light.addSpotLight(vector3df(_pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().X + 2.5f,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Y + 3.5f,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Z),
                                           1.0f, 20.0f, 1.0f, SColorf(1,1,1,1),SColorf(1,1,1,1),SColorf(1,1,1,1), vector3df(80, -90, -40));
          break;
        default :
          Core::Display.light.addSpotLight(vector3df(_pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().X,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Y + 3,
                                                     _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos().Z),
                                           1.0f, 20.0f, 1.0f, SColorf(1,1,1,1),SColorf(1,1,1,1),SColorf(1,1,1,1));
          break;
      }
      Display.camera.ZoomOnPlayer(_pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getPos(), _pmng->getPlayers()->at(_gameOver->getWinner() - 1)->getDirection());
      switch (_gameOver->getWinner())
      {
        case 1 :
          _pmng->getPlayers()->at(0)->victoryEffect({video::SColor(255,255,255,255), video::SColor(255,255,255,255)});
          break ;
        case 2 :
          _pmng->getPlayers()->at(1)->victoryEffect({video::SColor(0,150,0,240), video::SColor(0,150,0,240)});
          break ;
        case 3 :
          _pmng->getPlayers()->at(2)->victoryEffect({video::SColor(255,0,204,0), video::SColor(255,0,204,0)});
          break ;
        case 4 :
          _pmng->getPlayers()->at(3)->victoryEffect({video::SColor(255,255,0,0), video::SColor(255,255,255,0)});
          break ;
        }
    }
  }

  void Core::ChangeDisplay(Indie::SwitchDisplay dSwitch) {
    switch (dSwitch) {
      case Indie::TO_MENU :
        DisplaySwitch<Indie::TO_MENU>(); break;
      case Indie::TO_START_GAME :
        DisplaySwitch<Indie::TO_START_GAME>(); break;
      case Indie::TO_GAME :
        DisplaySwitch<Indie::TO_GAME>(); break;
      case Indie::TO_IG_SETS :
        DisplaySwitch<Indie::TO_IG_SETS>(); break;
      case Indie::TO_GAME_PAUSED :
        DisplaySwitch<Indie::TO_GAME_PAUSED>(); break ;
      case Indie::TO_END :
        DisplaySwitch<Indie::TO_END>(); break ;
      default : break ;
    }
    DisplayEngine::dSwitch = Indie::NOOP;
}

void Core::updateFR(void) {
	Core::frameRate = static_cast<float>(1.0) / static_cast<float>(Core::Display.driver->getFPS() ? Core::Display.driver->getFPS() : 60);
  Core::speedRatio = ((1.0f / 60.0f) / Core::frameRate);
}

void Core::run(void)
{
  while (Display.device->run()) {
    Core::Time = std::chrono::system_clock::now();
    if (DisplayEngine::dSwitch != Indie::NOOP)
    {
      ChangeDisplay(DisplayEngine::dSwitch);
      Core::frameRate = 0.016f;
      continue ;
    }
    switch (DisplayEngine::dInstance) {
      case Indie::MENU :
        update<Indie::MENU>();
        break ;
      case Indie::START_GAME :
        update<Indie::START_GAME>();
        break ;
      case Indie::GAME :
        update<Indie::GAME>();
        break ;
      case Indie::IG_SETS :
        update<Indie::IG_SETS>();
        break ;
      case Indie::GAME_PAUSED :
        update<Indie::GAME_PAUSED>();
        break ;
      case Indie::END_GAME :
        update<Indie::END_GAME>();
        break ;
      default :;
    }
    this->updateFR();
    Display.render();
  }
}
