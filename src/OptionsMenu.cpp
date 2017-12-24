/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-17T13:07:16+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T11:03:52+02:00
 */

#include <irrlicht/irrlicht.h>
#include "MenuScreens.hpp"
#include "Text.hpp"
#include "Menu.hpp"
#include "Core.hpp"

int OptionsScreen::currPlayer = 0;
short OptionsScreen::s_to_map = -1;
std::unordered_map<irr::EKEY_CODE, std::string, HashType<irr::EKEY_CODE>> OptionsScreen::KeyString = {};

OptionsScreen::OptionsScreen() : _players({"Player One","Player Two","Player Three","Player Four"})
{
  std::ifstream ifs(CONF("SoundSets.conf"));
  try {
    boost::archive::text_iarchive ia(ifs);
    ia >> Core::Sound.Sets;
  }
  catch ( const boost::archive::archive_exception & ) {
    Core::Sound.Sets = {100, 100, 100, false};
  }
  KeyString = {
    {static_cast<irr::EKEY_CODE>(-1), "<UNDEFINED>"},
    {irr::EKEY_CODE::KEY_BACK,"BACKSPACE"},
    {irr::EKEY_CODE::KEY_TAB, "TAB"},
    {irr::EKEY_CODE::KEY_CAPITAL, "CAPS LOCK"},
    {irr::EKEY_CODE::KEY_RETURN, "ENTER"},
    {irr::EKEY_CODE::KEY_PAUSE, "PAUSE"},
    {irr::EKEY_CODE::KEY_SPACE, "SPACE"},
    {irr::EKEY_CODE::KEY_PRIOR, "PGUP"},
    {irr::EKEY_CODE::KEY_NEXT, "PGDOWN"},
    {irr::EKEY_CODE::KEY_END, "END"},
    {irr::EKEY_CODE::KEY_HOME, "HOME"},
    {irr::EKEY_CODE::KEY_INSERT, "INS"},
    {irr::EKEY_CODE::KEY_DELETE, "DEL"},
    {irr::EKEY_CODE::KEY_LEFT, "LEFT"}, {irr::EKEY_CODE::KEY_UP, "UP"}, {irr::EKEY_CODE::KEY_RIGHT, "RIGHT"}, {irr::EKEY_CODE::KEY_DOWN, "DOWN"},
    {irr::EKEY_CODE::KEY_KEY_0, "0"}, {irr::EKEY_CODE::KEY_KEY_1, "1"}, {irr::EKEY_CODE::KEY_KEY_2, "2"}, {irr::EKEY_CODE::KEY_KEY_3, "3"}, {irr::EKEY_CODE::KEY_KEY_4, "4"}, {irr::EKEY_CODE::KEY_KEY_5, "5"}, {irr::EKEY_CODE::KEY_KEY_6, "6"}, {irr::EKEY_CODE::KEY_KEY_7, "7"}, {irr::EKEY_CODE::KEY_KEY_8, "8"}, {irr::EKEY_CODE::KEY_KEY_9, "9"},
    {irr::EKEY_CODE::KEY_KEY_A, "A"}, {irr::EKEY_CODE::KEY_KEY_B, "B"}, {irr::EKEY_CODE::KEY_KEY_C, "C"}, {irr::EKEY_CODE::KEY_KEY_D, "D"}, {irr::EKEY_CODE::KEY_KEY_E, "E"}, {irr::EKEY_CODE::KEY_KEY_F, "F"}, {irr::EKEY_CODE::KEY_KEY_G, "G"}, {irr::EKEY_CODE::KEY_KEY_H, "H"}, {irr::EKEY_CODE::KEY_KEY_I, "I"}, {irr::EKEY_CODE::KEY_KEY_J, "J"}, {irr::EKEY_CODE::KEY_KEY_K, "K"}, {irr::EKEY_CODE::KEY_KEY_L, "L"}, {irr::EKEY_CODE::KEY_KEY_M, "M"}, {irr::EKEY_CODE::KEY_KEY_N, "N"},   {irr::EKEY_CODE::KEY_KEY_O, "O"}, {irr::EKEY_CODE::KEY_KEY_P, "P"}, {irr::EKEY_CODE::KEY_KEY_Q, "Q"}, {irr::EKEY_CODE::KEY_KEY_R, "R"}, {irr::EKEY_CODE::KEY_KEY_S, "S"}, {irr::EKEY_CODE::KEY_KEY_T, "T"}, {irr::EKEY_CODE::KEY_KEY_U, "U"}, {irr::EKEY_CODE::KEY_KEY_V, "V"}, {irr::EKEY_CODE::KEY_KEY_W, "W"}, {irr::EKEY_CODE::KEY_KEY_X, "X"}, {irr::EKEY_CODE::KEY_KEY_Y, "Y"}, {irr::EKEY_CODE::KEY_KEY_Z, "Z"},
    {irr::EKEY_CODE::KEY_NUMPAD0, "NUM 0"}, {irr::EKEY_CODE::KEY_NUMPAD1, "NUM 1"}, {irr::EKEY_CODE::KEY_NUMPAD2, "NUM 2"}, {irr::EKEY_CODE::KEY_NUMPAD3, "NUM 3"}, {irr::EKEY_CODE::KEY_NUMPAD4, "NUM 4"}, {irr::EKEY_CODE::KEY_NUMPAD5, "NUM 5"}, {irr::EKEY_CODE::KEY_NUMPAD6, "NUM 6"}, {irr::EKEY_CODE::KEY_NUMPAD7, "NUM 7"}, {irr::EKEY_CODE::KEY_NUMPAD8, "NUM 8"}, {irr::EKEY_CODE::KEY_NUMPAD9, "NUM 9"}, {irr::EKEY_CODE::KEY_MULTIPLY, "NUM *"}, {irr::EKEY_CODE::KEY_ADD, "NUM +"},  {irr::EKEY_CODE::KEY_SUBTRACT, "NUM -"}, {irr::EKEY_CODE::KEY_DIVIDE, "NUM /"},
    {irr::EKEY_CODE::KEY_F1, "F1"}, {irr::EKEY_CODE::KEY_F2, "F2"}, {irr::EKEY_CODE::KEY_F3, "F3"}, {irr::EKEY_CODE::KEY_F4, "F4"}, {irr::EKEY_CODE::KEY_F5, "F5"}, {irr::EKEY_CODE::KEY_F6, "F6"}, {irr::EKEY_CODE::KEY_F7, "F7"}, {irr::EKEY_CODE::KEY_F8, "F8"}, {irr::EKEY_CODE::KEY_F9, "F9"}, {irr::EKEY_CODE::KEY_F10, "F10"}, {irr::EKEY_CODE::KEY_F11, "F11"}, {irr::EKEY_CODE::KEY_F12, "F12"},
    {irr::EKEY_CODE::KEY_MENU, "ALT"}, {irr::EKEY_CODE::KEY_LMENU, "LALT"}, {irr::EKEY_CODE::KEY_RMENU, "RALT"},
    {irr::EKEY_CODE::KEY_SHIFT, "SHIFT"}, {irr::EKEY_CODE::KEY_LSHIFT, "LSHIFT"}, {irr::EKEY_CODE::KEY_RSHIFT, "RSHIFT"},
    {irr::EKEY_CODE::KEY_CONTROL, "CTRL"}, {irr::EKEY_CODE::KEY_LCONTROL, "LCTRL"}, {irr::EKEY_CODE::KEY_RCONTROL, "RCTRL"},
    {irr::EKEY_CODE::KEY_LWIN, "LWIN"}, {irr::EKEY_CODE::KEY_RWIN, "RWIN"},
    {irr::EKEY_CODE::KEY_OEM_1, ";"},
    {irr::EKEY_CODE::KEY_PLUS, "="},
    {irr::EKEY_CODE::KEY_COMMA, ","},
    {irr::EKEY_CODE::KEY_MINUS, "-"},
    {irr::EKEY_CODE::KEY_PERIOD, "."},
    {irr::EKEY_CODE::KEY_OEM_2, "/"},
    {irr::EKEY_CODE::KEY_OEM_3, "`"},
    {irr::EKEY_CODE::KEY_OEM_4, "["},
    {irr::EKEY_CODE::KEY_OEM_5, "\\"},
    {irr::EKEY_CODE::KEY_OEM_6, "]"},
    {irr::EKEY_CODE::KEY_OEM_7, "'"},
    {irr::EKEY_CODE::KEY_OEM_102, "<"}
  };
}

void OptionsScreen::sceneSetter(const Settings &settings)
{
    ITexture* image = Core::Display.driver->getTexture(IMAGE("SettingsBackground"));
    Core::Display.env->addImage(image, position2d<int>(0,0));

    /*
    ** GUI Buttons
    */

    Button Done(IMAGE("ApplyButton"), IMAGE("ApplyButtonPressed"),
                 rect<s32>(X(6),Y(9.4),X(9),Y(9.9)), Indie::MenuButtons::APPLY_BUTTON);
    Button Default(IMAGE("DefaultButton"), IMAGE("DefaultButtonPressed"),
                   rect<s32>(X(11),Y(9.4),X(14),Y(9.9)), Indie::MenuButtons::DEFAULT_BUTTON);

    /*
    ** Volume Settings Buttons
    */

    IGUIImage *Filter = Core::Display.env->addImage(rect<s32>(X(2), Y(2), X(6.5) + 100, Y(7) + 150));
    Filter->setImage(Core::Display.driver->getTexture(IMAGE("DarkFilter")));

    Text SoundTxt("Sound", rect<s32>(X(2), Y(1.2), X(6.5) + 100, Y(2)), 50, SColor(255,255,255,255), false, "", EGUIA_CENTER);

    Button buttonMinusMaster(IMAGE("MinusButton"), IMAGE("MinusButtonPressed"),
                            rect<s32>(X(2), Y(2.5), X(2)+ 100, Y(2.5) + 100), Indie::MenuButtons::MASTERDOWN);
    IGUIImage *Volume = Core::Display.env->addImage(rect<s32>(X(2) + 120, Y(2.5), static_cast<s32>(X(2) +120+ ((X(4.5) - 140) * (static_cast<float>(Core::Sound.Sets.MasterVolume) / 100.0f))), Y(2.5) + 100));
    Volume->setImage(Core::Display.driver->getTexture(IMAGE("VolumeBar")));
    Button buttonPlusMaster(IMAGE("PlusButton"), IMAGE("PlusButtonPressed"),
                             rect<s32>(X(6.5), Y(2.5), X(6.5) + 100, Y(2.5) + 100), Indie::MenuButtons::MASTERUP);
    Button buttonMinusMusic(IMAGE("MinusButton"), IMAGE("MinusButtonPressed"),
                            rect<s32>(X(2), Y(4), X(2)+ 100, Y(4) + 100), Indie::MenuButtons::MUSICDOWN);
    Volume = Core::Display.env->addImage(rect<s32>(X(2) + 120, Y(4), static_cast<s32>(X(2)+120 + ((X(4.5) - 140)  * static_cast<float>(Core::Sound.Sets.MusicVolume) / 100.0f)), Y(4) + 100));
    Volume->setImage(Core::Display.driver->getTexture(IMAGE("VolumeBar")));
    Button buttonPlusMusic(IMAGE("PlusButton"), IMAGE("PlusButtonPressed"),
                          rect<s32>(X(6.5), Y(4), X(6.5) + 100, Y(4) + 100), Indie::MenuButtons::MUSICUP);
    Button buttonMinusFx(IMAGE("MinusButton"), IMAGE("MinusButtonPressed"),
                        rect<s32>(X(2), Y(5.5), X(2)+ 100, Y(5.5) + 100), Indie::MenuButtons::FXDOWN);
    Volume = Core::Display.env->addImage(rect<s32>(X(2) + 120, Y(5.5), static_cast<s32>(X(2) +120+ ((X(4.5) - 140) * (static_cast<float>(Core::Sound.Sets.FXVolume) / 100.0f))), Y(5.5) + 100));
    Volume->setImage(Core::Display.driver->getTexture(IMAGE("VolumeBar")));
    Button buttonPlusFx(IMAGE("PlusButton"), IMAGE("PlusButtonPressed"),
                        rect<s32>(X(6.5), Y(5.5), X(6.5) + 100, Y(5.5) + 100), Indie::MenuButtons::FXUP);
    if (Core::Sound.Sets.Mute == false)
      Button buttonMute(IMAGE("MuteButton"), IMAGE("UnMuteButton"),
                        rect<s32>(X(2.5), Y(7), X(6) +100, Y(7) + 100), Indie::MenuButtons::MUTE);
    else
      Button buttonMute(IMAGE("UnMuteButton"), IMAGE("MuteButton"),
                        rect<s32>(X(2.5), Y(7), X(6) +100, Y(7) + 100), Indie::MenuButtons::MUTE);

    Text MainVolume("Master", rect<s32>(X(2) + 120, Y(2.5), X(2) + X(4.5) - 20, Y(2.5) + 100), 75, SColor(255,255,255,255), false, "", EGUIA_CENTER);
    Text MusicVolume("Music", rect<s32>(X(2) + 120, Y(4), X(2) + X(4.5) - 20, Y(4) + 100), 75, SColor(255,255,255,255), false, "", EGUIA_CENTER);
    Text EffectVolume("FX", rect<s32>(X(2) + 120, Y(5.5), X(2) + (X(4.5) - 20), Y(5.5) + 100), 75, SColor(255,255,255,255), false, "", EGUIA_CENTER);


    /*
    ** KeyBinds Settings Buttons
    */

    Filter = Core::Display.env->addImage(rect<s32>(X(13.5) - 100, Y(2), X(18), Y(7) + 150));
    Filter->setImage(Core::Display.driver->getTexture(IMAGE("DarkFilter")));

    Text currPlayer(this->_players[OptionsScreen::currPlayer], rect<s32>(X(13.5), Y(1.2), X(18) - 100, Y(2)), 50, SColor(255,255,255,255), false, "", EGUIA_CENTER);
    Button  LeftArrow(IMAGE("LeftArrow"), IMAGE("LeftArrowPressed"),
                       rect<s32>(X(13.5) - 100, Y(2) - 90, X(13.5), Y(2) + 10), Indie::MenuButtons::SWAPLEFT);
    Button  RightArrow(IMAGE("RightArrow"), IMAGE("RightArrowPressed"),
                       rect<s32>(X(18) - 100, Y(2) - 90, X(18), Y(2) + 10), Indie::MenuButtons::SWAPRIGHT);

    IGUIImage *Icon = Core::Display.env->addImage(rect<s32>(X(13.5) - 100, Y(2.5), X(13.5), Y(2.5) + 100));
    Icon->setImage(Core::Display.driver->getTexture(IMAGE("UpIcon")));
    auto i = KeyString.find(settings.players[OptionsScreen::currPlayer].keyMap.up);
    if (i != KeyString.end())
    Text KeyTxt(i->second, rect<s32>(X(13.5), Y(2.5), X(17.5), Y(2.5) + 100), 50);
    Button  UpModifier(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                       rect<s32>(X(13.5), Y(2.5), X(17.5), Y(2.5) + 100), Indie::MenuButtons::UPMOD);

    Icon = Core::Display.env->addImage(rect<s32>(X(13.5) - 100, Y(3.6), X(13.5), Y(3.6) + 100));
    Icon->setImage(Core::Display.driver->getTexture(IMAGE("DownIcon")));
    i = KeyString.find(settings.players[OptionsScreen::currPlayer].keyMap.down);
    if (i != KeyString.end())
      Text KeyTxt(i->second, rect<s32>(X(13.5), Y(3.6), X(17.5), Y(3.6) + 100), 50);
    Button  DownModifier(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                         rect<s32>(X(13.5), Y(3.6), X(17.5), Y(3.6) + 100), Indie::MenuButtons::DOMOD);

    Icon = Core::Display.env->addImage(rect<s32>(X(13.5) - 100, Y(4.7), X(13.5), Y(4.7) + 100));
    Icon->setImage(Core::Display.driver->getTexture(IMAGE("LeftIcon")));
    i = KeyString.find(settings.players[OptionsScreen::currPlayer].keyMap.left);
    if (i != KeyString.end())
      Text KeyTxt(i->second, rect<s32>(X(13.5), Y(4.7), X(17.5), Y(4.7) + 100), 50);
    Button  LeftModifier(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                         rect<s32>(X(13.5), Y(4.7), X(17.5), Y(4.7) + 100), Indie::MenuButtons::LEMOD);

    Icon = Core::Display.env->addImage(rect<s32>(X(13.5) - 100, Y(5.8), X(13.5), Y(5.8) + 100));
    Icon->setImage(Core::Display.driver->getTexture(IMAGE("RightIcon")));
    i = KeyString.find(settings.players[OptionsScreen::currPlayer].keyMap.right);
    if (i != KeyString.end())
      Text KeyTxt(i->second, rect<s32>(X(13.5), Y(5.8), X(17.5), Y(5.8) + 100), 50);
    Button  RightModifier(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                          rect<s32>(X(13.5), Y(5.8), X(17.5), Y(5.8) + 100), Indie::MenuButtons::RIMOD);

    Icon = Core::Display.env->addImage(rect<s32>(X(13.5) - 100, Y(6.9), X(13.5), Y(6.9) + 100));
    Icon->setImage(Core::Display.driver->getTexture(IMAGE("ActionIcon")));
    i = KeyString.find(settings.players[OptionsScreen::currPlayer].keyMap.action);
    if (i != KeyString.end())
      Text KeyTxt(i->second, rect<s32>(X(13.5), Y(6.9), X(17.5), Y(6.9)+100), 50);
    Button  ActionModifier(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                           rect<s32>(X(13.5), Y(6.9), X(17.5), Y(6.9)+100), Indie::MenuButtons::ACMOD);

}
