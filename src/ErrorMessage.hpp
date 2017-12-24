/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-22T17:46:28+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T19:34:50+02:00
 */

#ifndef POPUP_HPP
# define POPUP_HPP

#include <memory>
#include <chrono>
#include "Indie.hpp"
#include "Core.hpp"

class APopUp {
  public:
    virtual ~APopUp() {}

    virtual void Ok() const = 0;
    virtual void Dismiss() const = 0;

  protected:
    void init(const std::string &message, bool okButton, bool dismissButton, const io::path &filterTex = IMAGE("DarkFilterPopUp"));
};

class PopUpManager {
  public:
    PopUpManager() = default;
    ~PopUpManager() = default;

    void create(const APopUp *pop) {
      _popup.reset(pop);
    }
    void Ok() { if (_popup.get() != nullptr) {_popup->Ok();} }
    void Dismiss() { if (_popup.get() != nullptr) {_popup->Dismiss();} }
  private:
    std::unique_ptr<const APopUp> _popup;
};

#endif
