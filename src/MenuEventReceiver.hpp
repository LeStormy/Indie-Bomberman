/*
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-16T18:38:25+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:11:39+02:00
*/

#ifndef MENUEVENTRECEIVER_HPP
# define MENUEVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>
#include <unordered_map>
#include <functional>
#include "Settings.hpp"
#include "Menu.hpp"
#include "Text.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MenuEventReceiver : public IEventReceiver
{
public:
  MenuEventReceiver(SAppContext & Context);

    bool OnEvent(const SEvent& event);

/* Menu Functions */
    void Quit() const;
    void ToMainPage() const;
	  void ToScoreBoard() const;
    void ToNewGamePage() const;
    void ToSettingsPage() const;
    void ToGame();

/* Settings Functions */
    void MasterUp() const;
    void MasterDown() const;
    void MusicUp() const;
    void MusicDown() const;
    void FxUp() const;
    void FxDown() const;
    void Mute() const;
    void SwapLeft() const;
    void SwapRight() const;
    void DefaultSets();
    void ApplySettings() const;

/* KeyBinds Functions */
    void ChangeKey(const EKEY_CODE &keyPressed);
    void ChangeKeyUp() const;
    void ChangeKeyDown() const;
    void ChangeKeyLeft() const;
    void ChangeKeyRight() const;
    void ChangeKeyAction() const;

/* SetGame Functions */
    void setName(const SEvent::SKeyInput &keyPressed);
    void changeName1() const;
    void changeName2() const;
    void changeName3() const;
    void changeName4() const;
    void ChangeType(s32 id);
    void ToCustom() const;
    void ToPremade() const;
    void PlusWidth();
    void MinusWidth();
    void PlusHeight();
    void MinusHeight();
    void PrevBiome();
    void NextBiome();
    void PlatformNext();
    void Reroll();
    void PrevMap() const;
    void NextMap() const;
/* LoadGame Functions */

/* Miscellaneous */
    void PopUpOk() const;
    void PopUpDismiss() const;

private:
  void ReplaceKey(const EKEY_CODE &keyPressed) const;
  bool TooManyUnused();

  SAppContext Context;
  std::unordered_map<Indie::MenuButtons, std::function<void()>, HashType<Indie::MenuButtons>> ButtonFunctions;
  std::string nameTmp;
  Text nameDisp;
  bool typing;
};

#endif
