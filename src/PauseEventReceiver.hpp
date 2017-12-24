/**
 * @Author: raph
 * @Date:   2017-06-08T19:04:18+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:04:13+02:00
 */

#ifndef PAUSEEVENTRECEIVER_HPP
# define PAUSEEVENTRECEIVER_HPP

#include <unordered_map>
#include "Indie.hpp"
#include "Settings.hpp"
#include "Menu.hpp"

class PauseEventReceiver : public IEventReceiver {
public:
  PauseEventReceiver(SAppContext & Context);

  bool OnEvent(const SEvent& event);

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

private:
  void ReplaceKey(const EKEY_CODE &keyPressed) const;

  SAppContext Context;
  std::unordered_map<Indie::MenuButtons, std::function<void()>, HashType<Indie::MenuButtons>> ButtonFunctions;
};

#endif
