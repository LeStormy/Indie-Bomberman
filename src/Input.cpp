/**
 * @Author: raph
 * @Date:   2017-06-07T13:37:18+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-17T20:38:45+02:00
 */



//
// Created by baptiste on 5/12/17.
//

#include <iostream>
#include <algorithm>
#include "Input.hpp"
#include "Indie.hpp"
#include "DisplayEngine.hpp"
#include "HudSet.hpp"
#include "APlayer.hpp"
#include "Core.hpp"

Input::Input(const std::array<KeyMap, 4> &playerKeyMap)
  : _playerKeyMap(playerKeyMap)
{
}

bool    Input::OnEvent(const irr::SEvent& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown && event.KeyInput.Key == irr::KEY_ESCAPE)
  {
    Core::Sound.playSound(AUDIO("Button"));
    if (DisplayEngine::dInstance == Indie::GAME)
      DisplayEngine::dSwitch = Indie::TO_GAME_PAUSED;
    else if (DisplayEngine::dInstance == Indie::GAME_PAUSED)
      DisplayEngine::dSwitch = Indie::TO_GAME;
    else if (DisplayEngine::dInstance == Indie::IG_SETS)
      DisplayEngine::dSwitch = Indie::TO_GAME_PAUSED;
    return true;
  }
  if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown && event.KeyInput.Key == irr::KEY_F1)
	  Hud::Save = true;
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
  {
    this->_key[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return true;
  }
  if (event.EventType == EET_GUI_EVENT)
  {
    s32 id = event.GUIEvent.Caller->getID();
    switch(event.GUIEvent.EventType)
    {
      case EGET_BUTTON_CLICKED:
      {
        switch (id)
        {
          case 0:
            DisplayEngine::dSwitch = Indie::TO_GAME;
            Core::Sound.playSound(AUDIO("Button"));
            break ;
          case 1:
            DisplayEngine::dSwitch = Indie::TO_IG_SETS;
            Core::Sound.playSound(AUDIO("Button"));
            break ;
          case 2:
            DisplayEngine::dSwitch = Indie::TO_MENU;
            Core::Sound.playSound(AUDIO("Button"));
            break ;
        }
      }
      default:
        break;
    }
    return true;
  }

  return false;
}

std::array<bool, 5>    Input::getPlayerAction(const uint8_t id) const
{
  return (std::array<bool, 5>{this->_key[this->_playerKeyMap[id].up],
			      this->_key[this->_playerKeyMap[id].down],
			      this->_key[this->_playerKeyMap[id].left],
			      this->_key[this->_playerKeyMap[id].right],
			      this->_key[this->_playerKeyMap[id].action]});
}

void			Input::changeKeys(const std::array<KeyMap, 4> &keys)
{
  for (uint8_t i = 0; i < 4; i++)
	this->_playerKeyMap[i] = keys.at(i);
}
