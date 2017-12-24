/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-24T16:29:22+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T22:00:03+02:00
 */
//
// Created by baptiste on 5/24/17.
//

#include "Menu.hpp"
#include "Core.hpp"
#include "MenuScreens.hpp"
#include "Warning.hpp"
#include "Loader.hpp"
#include "MenuEventReceiver.hpp"
#include "HudSet.hpp"

MenuEventReceiver::MenuEventReceiver(SAppContext & Context) : Context(Context), nameTmp(""), nameDisp(Text("", rect<s32>(0,0,0,0), 50)), typing(false) {
/* Menu Functions */
  this->ButtonFunctions[Indie::MenuButtons::QUIT_BUTTON] = std::bind(&MenuEventReceiver::Quit, this);
  this->ButtonFunctions[Indie::MenuButtons::MAINPAGE_BUTTON] = std::bind(&MenuEventReceiver::ToMainPage, this);
  this->ButtonFunctions[Indie::MenuButtons::SCOREBOARD_BUTTON] = std::bind(&MenuEventReceiver::ToScoreBoard, this);
  this->ButtonFunctions[Indie::MenuButtons::SETGAME_BUTTON] = std::bind(&MenuEventReceiver::ToNewGamePage, this);
  this->ButtonFunctions[Indie::MenuButtons::OPTIONS_BUTTON] = std::bind(&MenuEventReceiver::ToSettingsPage, this);
  this->ButtonFunctions[Indie::MenuButtons::OUTOFMENU_BUTTON] = std::bind(&MenuEventReceiver::ToGame, this);

/* Settings Functions */
  this->ButtonFunctions[Indie::MenuButtons::MASTERUP] = std::bind(&MenuEventReceiver::MasterUp, this);
  this->ButtonFunctions[Indie::MenuButtons::MASTERDOWN] = std::bind(&MenuEventReceiver::MasterDown, this);
  this->ButtonFunctions[Indie::MenuButtons::MUSICUP] = std::bind(&MenuEventReceiver::MusicUp, this);
  this->ButtonFunctions[Indie::MenuButtons::MUSICDOWN] = std::bind(&MenuEventReceiver::MusicDown, this);
  this->ButtonFunctions[Indie::MenuButtons::FXUP] = std::bind(&MenuEventReceiver::FxUp, this);
  this->ButtonFunctions[Indie::MenuButtons::FXDOWN] = std::bind(&MenuEventReceiver::FxDown, this);
  this->ButtonFunctions[Indie::MenuButtons::MUTE] = std::bind(&MenuEventReceiver::Mute, this);
  this->ButtonFunctions[Indie::MenuButtons::SWAPLEFT] = std::bind(&MenuEventReceiver::SwapLeft, this);
  this->ButtonFunctions[Indie::MenuButtons::SWAPRIGHT] = std::bind(&MenuEventReceiver::SwapRight, this);
  this->ButtonFunctions[Indie::MenuButtons::DEFAULT_BUTTON] = std::bind(&MenuEventReceiver::DefaultSets, this);
  this->ButtonFunctions[Indie::MenuButtons::APPLY_BUTTON] = std::bind(&MenuEventReceiver::ApplySettings, this);

/* KeyBinds Functions */
  this->ButtonFunctions[Indie::MenuButtons::UPMOD] = std::bind(&MenuEventReceiver::ChangeKeyUp, this);
  this->ButtonFunctions[Indie::MenuButtons::DOMOD] = std::bind(&MenuEventReceiver::ChangeKeyDown, this);
  this->ButtonFunctions[Indie::MenuButtons::LEMOD] = std::bind(&MenuEventReceiver::ChangeKeyLeft, this);
  this->ButtonFunctions[Indie::MenuButtons::RIMOD] = std::bind(&MenuEventReceiver::ChangeKeyRight, this);
  this->ButtonFunctions[Indie::MenuButtons::ACMOD] = std::bind(&MenuEventReceiver::ChangeKeyAction, this);

/* SetGame Functions */
  this->ButtonFunctions[Indie::MenuButtons::CUSTOM_BUTTON] = std::bind(&MenuEventReceiver::ToCustom, this);
  this->ButtonFunctions[Indie::MenuButtons::PREMADE_BUTTON] = std::bind(&MenuEventReceiver::ToPremade, this);
  this->ButtonFunctions[Indie::MenuButtons::MHEIGHT_BUTTON] = std::bind(&MenuEventReceiver::MinusHeight, this);
  this->ButtonFunctions[Indie::MenuButtons::PHEIGHT_BUTTON] = std::bind(&MenuEventReceiver::PlusHeight, this);
  this->ButtonFunctions[Indie::MenuButtons::MWIDTH_BUTTON] = std::bind(&MenuEventReceiver::MinusWidth, this);
  this->ButtonFunctions[Indie::MenuButtons::PWIDTH_BUTTON] = std::bind(&MenuEventReceiver::PlusWidth, this);
  this->ButtonFunctions[Indie::MenuButtons::PREVBIOME_BUTTON] = std::bind(&MenuEventReceiver::PrevBiome, this);
  this->ButtonFunctions[Indie::MenuButtons::NEXTBIOME_BUTTON] = std::bind(&MenuEventReceiver::NextBiome, this);
  this->ButtonFunctions[Indie::MenuButtons::PLATFORM_BUTTON] = std::bind(&MenuEventReceiver::PlatformNext, this);
  this->ButtonFunctions[Indie::MenuButtons::REROLL_BUTTON] = std::bind(&MenuEventReceiver::Reroll, this);
  this->ButtonFunctions[Indie::MenuButtons::PREVMAP_BUTTON] = std::bind(&MenuEventReceiver::PrevMap, this);
  this->ButtonFunctions[Indie::MenuButtons::NEXTMAP_BUTTON] = std::bind(&MenuEventReceiver::NextMap, this);
  this->ButtonFunctions[Indie::MenuButtons::CHANGENAME1_BUTTON] = std::bind(&MenuEventReceiver::changeName1, this);
  this->ButtonFunctions[Indie::MenuButtons::CHANGENAME2_BUTTON] = std::bind(&MenuEventReceiver::changeName2, this);
  this->ButtonFunctions[Indie::MenuButtons::CHANGENAME3_BUTTON] = std::bind(&MenuEventReceiver::changeName3, this);
  this->ButtonFunctions[Indie::MenuButtons::CHANGENAME4_BUTTON] = std::bind(&MenuEventReceiver::changeName4, this);

/* LoadGame Functions */

/* Miscellaneous */
  this->ButtonFunctions[Indie::MenuButtons::OK_BUTTON] = std::bind(&MenuEventReceiver::PopUpOk, this);
  this->ButtonFunctions[Indie::MenuButtons::DISMISS_BUTTON] = std::bind(&MenuEventReceiver::PopUpDismiss, this);
}

bool MenuEventReceiver::OnEvent(const SEvent& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
      event.KeyInput.Key == irr::KEY_ESCAPE &&
      event.KeyInput.PressedDown)
  {
    if (Menu::currScreen == Indie::CurrentScreen::SPLASH)
    {
      Menu::currScreen = Indie::CurrentScreen::MAINPAGE;
      Menu::reloadScreen = true;
      Core::Display.camera.cancelEffect();
      Core::Display.smgr->clear();
      Core::Sound.stopAll();
      Core::Sound.playMusic(AUDIO("MenuMusic"));
      return true;
    }
  }
  if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
      event.KeyInput.PressedDown)
  {
    if (Menu::currScreen == Indie::CurrentScreen::OPTIONS && OptionsScreen::s_to_map != -1)
    {
      this->ChangeKey(event.KeyInput.Key);
      return true;
    }
    if (SetGameScreen::isChangingName != -1)
      this->setName(event.KeyInput);
  }
  if (event.EventType == EET_GUI_EVENT)
  {
    s32 id = event.GUIEvent.Caller->getID();
    switch(event.GUIEvent.EventType)
    {
      case EGET_BUTTON_CLICKED:
      {
        Menu::reloadScreen = true;
        auto i = ButtonFunctions.find(static_cast<Indie::MenuButtons>(id));
        if (i != ButtonFunctions.end())
          i->second();
        else if (id >= static_cast<int>(Indie::TYPE1_BUTTON) && id <= static_cast<int>(Indie::TYPE4_BUTTON))
          ChangeType(id);
        break;
      }
      default:
        break;
    }
    return true;
  }
  return false;
}

void MenuEventReceiver::ReplaceKey(const EKEY_CODE & keyPressed) const
{
  for (auto & it : this->Context.settings->players)
  {
    if (it.keyMap.up == keyPressed)
      it.keyMap.up = static_cast<irr::EKEY_CODE>(-1);
    else if (it.keyMap.down == keyPressed)
      it.keyMap.down = static_cast<irr::EKEY_CODE>(-1);
    else if (it.keyMap.left == keyPressed)
      it.keyMap.left = static_cast<irr::EKEY_CODE>(-1);
    else if (it.keyMap.right == keyPressed)
      it.keyMap.right = static_cast<irr::EKEY_CODE>(-1);
    else if (it.keyMap.action == keyPressed)
      it.keyMap.action = static_cast<irr::EKEY_CODE>(-1);
  }
}

void MenuEventReceiver::ChangeKey(const EKEY_CODE & keyPressed)
{
  this->ReplaceKey(keyPressed);
  switch (OptionsScreen::s_to_map)
  {
      case 0:
        this->Context.settings->players[OptionsScreen::currPlayer].keyMap.up = keyPressed;
        break;
      case 1:
        this->Context.settings->players[OptionsScreen::currPlayer].keyMap.down = keyPressed;
        break;
      case 2:
        this->Context.settings->players[OptionsScreen::currPlayer].keyMap.left = keyPressed;
        break;
      case 3:
        this->Context.settings->players[OptionsScreen::currPlayer].keyMap.right = keyPressed;
        break;
      case 4:
        this->Context.settings->players[OptionsScreen::currPlayer].keyMap.action = keyPressed;
        break;
      default:;
  }
  OptionsScreen::s_to_map = -1;;
  Menu::reloadScreen = true;
}

/******
******* GENERAL GUI
******/

void MenuEventReceiver::Quit() const
{
  LoadSave loader;
  Menu::currScreen = Indie::CurrentScreen::OUTOFMENU;
  loader.saveBinds(CONF("/Binds.conf"), std::array<KeyMap, 4>({Context.settings->players[0].keyMap, Context.settings->players[1].keyMap, Context.settings->players[2].keyMap, Context.settings->players[3].keyMap}));
  Core::Display.device->closeDevice();
}

void MenuEventReceiver::ToMainPage() const
{
  Menu::currScreen = Indie::CurrentScreen::MAINPAGE;
  Core::Sound.playSound(AUDIO("Button"));
}

void MenuEventReceiver::ToScoreBoard() const
{
	Menu::currScreen = Indie::CurrentScreen::SCOREBOARD;
  Core::Sound.playSound(AUDIO("Button"));
}

void MenuEventReceiver::ToNewGamePage() const
{
  Core::Sound.playSound(AUDIO("Button"));
  Menu::currScreen = Indie::CurrentScreen::SETGAME;
  if (DisplayEngine::dInstance != Indie::MENU)
    DisplayEngine::dSwitch = Indie::TO_MENU;
}

void MenuEventReceiver::ToSettingsPage() const
{
  Core::Sound.playSound(AUDIO("Button"));
  Menu::currScreen = Indie::CurrentScreen::OPTIONS;
}

void MenuEventReceiver::ToGame()
{
  Core::Sound.playSound(AUDIO("Button"));
  if (!SetGameScreen::customMap)
  {
    LoadSave loader;
    if (loader.loadPremadeMap(SetGameScreen::premadeIndex, *Context.settings) == 1)
      return ;
  }
  for (uint8_t i = 0; i < 4 ; i++)
    if (Context.settings->players[i].playerType == Indie::UNUSED_PLAYER)
      Context.settings->players[i].alive = false;
  Menu::currScreen = Indie::CurrentScreen::OUTOFMENU;
  Core::Sound.stopAll();
  DisplayEngine::dSwitch = Indie::TO_START_GAME;
}

/******
******* GENERAL SETTINGS
******/

void MenuEventReceiver::MasterUp() const
{
  if (Core::Sound.Sets.MasterVolume < 100)
  Core::Sound.Sets.MasterVolume += 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void MenuEventReceiver::MasterDown() const
{
  if (Core::Sound.Sets.MasterVolume > 0)
      Core::Sound.Sets.MasterVolume -= 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void MenuEventReceiver::MusicUp() const
{
  if (Core::Sound.Sets.MusicVolume < 100)
      Core::Sound.Sets.MusicVolume += 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void MenuEventReceiver::MusicDown() const
{
  if (Core::Sound.Sets.MusicVolume > 0)
      Core::Sound.Sets.MusicVolume -= 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void MenuEventReceiver::FxUp() const
{
  if (Core::Sound.Sets.FXVolume < 100)
      Core::Sound.Sets.FXVolume += 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void MenuEventReceiver::FxDown() const
{
  if (Core::Sound.Sets.FXVolume > 0)
      Core::Sound.Sets.FXVolume -= 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void MenuEventReceiver::Mute() const
{
  if (Core::Sound.Sets.Mute == true)
  {
    Core::Sound.Sets.Mute = false;
    if (Core::Sound.MainAudio.getStatus() == sf::SoundSource::Playing)
      Core::Sound.updateVolume();
    else
      (DisplayEngine::dInstance == Indie::MENU) ? (Core::Sound.playMusic(AUDIO("MenuMusic"))) : (Core::Sound.playMusic(AUDIO("GameMusic.ogg")));
  }
  else
  {
    Core::Sound.Sets.Mute = true;
    Core::Sound.MainAudio.setVolume(0);
    for (auto & it : Core::Sound.SoundEffectChannels)
      it.setVolume(0);
  }
}

void MenuEventReceiver::SwapLeft() const
{
  if (OptionsScreen::currPlayer > 0)
    --OptionsScreen::currPlayer;
  else
    OptionsScreen::currPlayer = 3;
}

void MenuEventReceiver::SwapRight() const
{
  if (OptionsScreen::currPlayer < 3)
    ++OptionsScreen::currPlayer;
  else
    OptionsScreen::currPlayer = 0;
}

void MenuEventReceiver::DefaultSets()
{
  LoadSave loader;
  loader.saveBinds(CONF("Binds.conf"), {
    KeyMap({EKEY_CODE::KEY_KEY_W, EKEY_CODE::KEY_KEY_S, EKEY_CODE::KEY_KEY_A, EKEY_CODE::KEY_KEY_D, EKEY_CODE::KEY_LSHIFT}),
    KeyMap({EKEY_CODE::KEY_UP, EKEY_CODE::KEY_DOWN, EKEY_CODE::KEY_LEFT, EKEY_CODE::KEY_RIGHT, EKEY_CODE::KEY_RSHIFT}),
    KeyMap({EKEY_CODE::KEY_KEY_F, EKEY_CODE::KEY_KEY_C, EKEY_CODE::KEY_KEY_X, EKEY_CODE::KEY_KEY_V, EKEY_CODE::KEY_KEY_Z}),
    KeyMap({EKEY_CODE::KEY_KEY_H, EKEY_CODE::KEY_KEY_N, EKEY_CODE::KEY_KEY_B, EKEY_CODE::KEY_KEY_M, EKEY_CODE::KEY_SPACE})
  });
  loader.loadBinds(CONF("Binds.conf"), Context.settings->players[0].keyMap,
                                       Context.settings->players[1].keyMap,
                                       Context.settings->players[2].keyMap,
                                       Context.settings->players[3].keyMap);
  Menu::DefaultSettings(*Context.settings);
  Core::Sound.Sets = {100, 100, 100, false};
  Core::Sound.updateVolume();
}

void MenuEventReceiver::ApplySettings() const
{
  Menu::currScreen = Indie::CurrentScreen::MAINPAGE;
  try {
    std::ofstream ofs(CONF("SoundSets.conf"));
    boost::archive::text_oarchive oa(ofs);
    oa << Core::Sound.Sets;
  }
  catch ( const boost::archive::archive_exception & ) {}
}

void MenuEventReceiver::ChangeKeyUp() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Up\""));
  OptionsScreen::s_to_map = 0;
}

void MenuEventReceiver::ChangeKeyDown() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Down\""));
  OptionsScreen::s_to_map = 1;
}

void MenuEventReceiver::ChangeKeyLeft() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Left\""));
  OptionsScreen::s_to_map = 2;
}

void MenuEventReceiver::ChangeKeyRight() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Right\""));
  OptionsScreen::s_to_map = 3;
}

void MenuEventReceiver::ChangeKeyAction() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Action\""));
  OptionsScreen::s_to_map = 4;
}

/******
******* SET GAME
******/

void MenuEventReceiver::setName(const SEvent::SKeyInput & keyPressed)
{
  bool _update = false;

  if (keyPressed.Key == irr::KEY_RETURN && this->nameTmp.size() > 0)
  {
    Context.settings->players[SetGameScreen::isChangingName].name = this->nameTmp;
    this->nameTmp = "";
    SetGameScreen::isChangingName = -1;
    Menu::reloadScreen = true;
    this->typing = false;
    return ;
  }
  else if (keyPressed.Key == irr::KEY_BACK && this->nameTmp.size() > 0)
  {
    _update = true;
    this->nameTmp.pop_back();
  }
  else if (this->nameTmp.size() < 10 && keyPressed.Char >= 32 && keyPressed.Char <= 126)
  {
    _update = true;
    this->nameTmp.push_back(static_cast<char>(keyPressed.Char));
  }
  else
    return ;
  if (this->typing && _update == true)
    nameDisp.guiTxt->remove();
  if (this->nameTmp.size() > 0)
    this->typing = true;
  else
    this->typing = false;
  nameDisp = Text(this->nameTmp, rect<s32>(X(7), Y(5), X(13), Y(7)), 50);
}

void MenuEventReceiver::changeName1() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("Enter Name for Player 1"));
  SetGameScreen::isChangingName = 0;
}

void MenuEventReceiver::changeName2() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("Enter Name for Player 2"));
  SetGameScreen::isChangingName = 1;
}

void MenuEventReceiver::changeName3() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("Enter Name for Player 3"));
  SetGameScreen::isChangingName = 2;
}

void MenuEventReceiver::changeName4() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("Enter Name for Player 4"));
  SetGameScreen::isChangingName = 3;
}

bool MenuEventReceiver::TooManyUnused()
{
  uint8_t unused = 0;
  for (uint8_t i = 0; i < 4; i++)
    if (Context.settings->players[i].playerType == Indie::UNUSED_PLAYER)
      ++unused;
  if (unused >= 2)
    return true;
  return false;
}

void MenuEventReceiver::ChangeType(s32 id)
{
  id -= static_cast<s32>(Indie::MenuButtons::TYPE1_BUTTON);
  switch (Context.settings->players[id].playerType) {
    case Indie::IA_PLAYER_EZ:
      Context.settings->players[id].playerType = Indie::IA_PLAYER_MED;
      break;
    case Indie::IA_PLAYER_MED:
      Context.settings->players[id].playerType = Indie::IA_PLAYER_HARD;
      break;
    case Indie::IA_PLAYER_HARD:
    {
      if (this->TooManyUnused() == true)
        Context.settings->players[id].playerType = Indie::HUMAN_PLAYER;
      else
        Context.settings->players[id].playerType = Indie::UNUSED_PLAYER;
      break;
    }
    case Indie::UNUSED_PLAYER:
      Context.settings->players[id].playerType = Indie::HUMAN_PLAYER;
      break;
    case Indie::HUMAN_PLAYER:
      Context.settings->players[id].playerType = Indie::IA_PLAYER_EZ;
      break;
  }
}

void MenuEventReceiver::ToPremade() const
{
  LoadSave loader;

  if (SetGameScreen::customMap == true)
    SetGameScreen::customMap = false;
}

void MenuEventReceiver::ToCustom() const
{
  if (SetGameScreen::customMap == false)
    SetGameScreen::customMap = true;
}

void MenuEventReceiver::PlusWidth()
{
  if (this->Context.settings->mapSet.mapSize.first < 14)
    this->Context.settings->mapSet.mapSize.first += 1;
}

void MenuEventReceiver::MinusWidth()
{
  if (this->Context.settings->mapSet.mapSize.first > 8)
    this->Context.settings->mapSet.mapSize.first -= 1;
}

void MenuEventReceiver::PlusHeight()
{
  if (this->Context.settings->mapSet.mapSize.second < 14)
    this->Context.settings->mapSet.mapSize.second += 1;
}

void MenuEventReceiver::MinusHeight()
{
  if (this->Context.settings->mapSet.mapSize.second > 8)
    this->Context.settings->mapSet.mapSize.second -= 1;
}

void MenuEventReceiver::PrevBiome()
{
  this->Context.settings->mapSet.Biome = static_cast<Indie::Biome>(static_cast<int>(this->Context.settings->mapSet.Biome) - 1);
  if (this->Context.settings->mapSet.Biome == Indie::Biome::BIOME_VOID)
    this->Context.settings->mapSet.Biome = static_cast<Indie::Biome>(static_cast<int>(Indie::Biome::BIOME_COUNT) - 1);
}

void MenuEventReceiver::NextBiome()
{
  this->Context.settings->mapSet.Biome = static_cast<Indie::Biome>(static_cast<int>(this->Context.settings->mapSet.Biome) + 1);
  if (this->Context.settings->mapSet.Biome == Indie::Biome::BIOME_COUNT)
    this->Context.settings->mapSet.Biome = static_cast<Indie::Biome>(0);
}

void MenuEventReceiver::PlatformNext()
{
  this->Context.settings->mapSet.platforms = ((this->Context.settings->mapSet.platforms == true) ? false : true);
}

void MenuEventReceiver::Reroll()
{
  this->Context.settings->mapSet.mapSize.first = ((std::rand() % (14 - 8 + 1)) + 8);
  this->Context.settings->mapSet.mapSize.second = ((std::rand() % (14 - 8 + 1)) + 8);
  this->Context.settings->mapSet.floorDensity = std::rand() % 101;
  this->Context.settings->mapSet.blockDensity = std::rand() % 101;
  this->Context.settings->mapSet.platforms = ((std::rand() % 2 == 0) ? true : false);
}

void MenuEventReceiver::PrevMap() const
{
  LoadSave loader;

  SetGameScreen::premadeIndex -= 1;
  if (SetGameScreen::premadeIndex >= SetGameScreen::premadeSize)
    SetGameScreen::premadeIndex = SetGameScreen::premadeSize;
}

void MenuEventReceiver::NextMap() const
{
  LoadSave loader;

  SetGameScreen::premadeIndex += 1;
  if (SetGameScreen::premadeIndex > SetGameScreen::premadeSize)
    SetGameScreen::premadeIndex = 0;
}

/******
******* MISC
******/

void MenuEventReceiver::PopUpOk() const
{
  Core::popUp.Ok();
  Core::Display.env->clear();
}

void MenuEventReceiver::PopUpDismiss() const
{
  Core::popUp.Dismiss();
  Core::Display.env->clear();
}
