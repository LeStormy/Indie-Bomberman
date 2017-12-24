/**
 * @Author: raph
 * @Date:   2017-06-08T19:03:46+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:06:39+02:00
 */

#include "PauseEventReceiver.hpp"
#include "DisplayEngine.hpp"
#include "Core.hpp"
#include "MenuScreens.hpp"
#include "ErrorMessage.hpp"
#include "Warning.hpp"
#include "Menu.hpp"

PauseEventReceiver::PauseEventReceiver(SAppContext & Context) : Context(Context)
{
  /* Settings Functions */
    this->ButtonFunctions[Indie::MenuButtons::MASTERUP] = std::bind(&PauseEventReceiver::MasterUp, this);
    this->ButtonFunctions[Indie::MenuButtons::MASTERDOWN] = std::bind(&PauseEventReceiver::MasterDown, this);
    this->ButtonFunctions[Indie::MenuButtons::MUSICUP] = std::bind(&PauseEventReceiver::MusicUp, this);
    this->ButtonFunctions[Indie::MenuButtons::MUSICDOWN] = std::bind(&PauseEventReceiver::MusicDown, this);
    this->ButtonFunctions[Indie::MenuButtons::FXUP] = std::bind(&PauseEventReceiver::FxUp, this);
    this->ButtonFunctions[Indie::MenuButtons::FXDOWN] = std::bind(&PauseEventReceiver::FxDown, this);
    this->ButtonFunctions[Indie::MenuButtons::MUTE] = std::bind(&PauseEventReceiver::Mute, this);
    this->ButtonFunctions[Indie::MenuButtons::SWAPLEFT] = std::bind(&PauseEventReceiver::SwapLeft, this);
    this->ButtonFunctions[Indie::MenuButtons::SWAPRIGHT] = std::bind(&PauseEventReceiver::SwapRight, this);
    this->ButtonFunctions[Indie::MenuButtons::DEFAULT_BUTTON] = std::bind(&PauseEventReceiver::DefaultSets, this);
    this->ButtonFunctions[Indie::MenuButtons::APPLY_BUTTON] = std::bind(&PauseEventReceiver::ApplySettings, this);

  /* KeyBinds Functions */
    this->ButtonFunctions[Indie::MenuButtons::UPMOD] = std::bind(&PauseEventReceiver::ChangeKeyUp, this);
    this->ButtonFunctions[Indie::MenuButtons::DOMOD] = std::bind(&PauseEventReceiver::ChangeKeyDown, this);
    this->ButtonFunctions[Indie::MenuButtons::LEMOD] = std::bind(&PauseEventReceiver::ChangeKeyLeft, this);
    this->ButtonFunctions[Indie::MenuButtons::RIMOD] = std::bind(&PauseEventReceiver::ChangeKeyRight, this);
    this->ButtonFunctions[Indie::MenuButtons::ACMOD] = std::bind(&PauseEventReceiver::ChangeKeyAction, this);

}

bool PauseEventReceiver::OnEvent(const SEvent& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT
      && event.KeyInput.Key == irr::KEY_ESCAPE
      && event.KeyInput.PressedDown)
  {
    DisplayEngine::dSwitch = Indie::TO_GAME_PAUSED;
    return true;
  }
  if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
      event.KeyInput.PressedDown)
  {
    if (OptionsScreen::s_to_map != -1)
    {
      this->ChangeKey(event.KeyInput.Key);
      return true;
    }
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
        break;
        //
      }
      default:
        break;
    }
    return true;
  }
  return false;
}

void PauseEventReceiver::ReplaceKey(const EKEY_CODE &keyPressed) const
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

void PauseEventReceiver::ChangeKey(const EKEY_CODE &keyPressed)
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
******* GENERAL SETTINGS
******/

void PauseEventReceiver::MasterUp() const
{
  if (Core::Sound.Sets.MasterVolume < 100)
    Core::Sound.Sets.MasterVolume += 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void PauseEventReceiver::MasterDown() const
{
  if (Core::Sound.Sets.MasterVolume > 0)
      Core::Sound.Sets.MasterVolume -= 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void PauseEventReceiver::MusicUp() const
{
  if (Core::Sound.Sets.MusicVolume < 100)
      Core::Sound.Sets.MusicVolume += 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void PauseEventReceiver::MusicDown() const
{
  if (Core::Sound.Sets.MusicVolume > 0)
      Core::Sound.Sets.MusicVolume -= 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void PauseEventReceiver::FxUp() const
{
  if (Core::Sound.Sets.FXVolume < 100)
      Core::Sound.Sets.FXVolume += 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void PauseEventReceiver::FxDown() const
{
  if (Core::Sound.Sets.FXVolume > 0)
      Core::Sound.Sets.FXVolume -= 5;
  if (Core::Sound.Sets.Mute == false)
    Core::Sound.updateVolume();
}

void PauseEventReceiver::Mute() const
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

void PauseEventReceiver::SwapLeft() const
{
  if (OptionsScreen::currPlayer > 0)
    --OptionsScreen::currPlayer;
  else
    OptionsScreen::currPlayer = 3;
}

void PauseEventReceiver::SwapRight() const
{
  if (OptionsScreen::currPlayer < 3)
    ++OptionsScreen::currPlayer;
  else
    OptionsScreen::currPlayer = 0;
}

void PauseEventReceiver::DefaultSets()
{
  Menu::DefaultSettings(*Context.settings);
  Core::Sound.Sets = {100, 100, 100, false};
  Core::Sound.updateVolume();
}

void PauseEventReceiver::ApplySettings() const
{
  DisplayEngine::dSwitch = Indie::TO_GAME_PAUSED;
  try {
    std::ofstream ofs(CONF("SoundSets.conf"));
    boost::archive::text_oarchive oa(ofs);
    oa << Core::Sound.Sets;
  }
  catch ( const boost::archive::archive_exception & ) {}
}

void PauseEventReceiver::ChangeKeyUp() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Up\""));
  OptionsScreen::s_to_map = 0;
}

void PauseEventReceiver::ChangeKeyDown() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Down\""));
  OptionsScreen::s_to_map = 1;
}

void PauseEventReceiver::ChangeKeyLeft() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Left\""));
  OptionsScreen::s_to_map = 2;
}

void PauseEventReceiver::ChangeKeyRight() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Moving Right\""));
  OptionsScreen::s_to_map = 3;
}

void PauseEventReceiver::ChangeKeyAction() const
{
  Menu::reloadScreen = false;
  Core::popUp.create(new MessagePop("PRESS A KEY TO CHANGE \"Action\""));
  OptionsScreen::s_to_map = 4;
}
