/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-25T13:17:12+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:43:32+02:00
 */

#ifndef TEXT_HPP
# define TEXT_HPP

#include "Indie.hpp"
#include "CGUITTFont.h"

class Text {
public:
  Text(const std::string &txt, const rect<s32> &pos, int fontSize,
       SColor color = SColor(255,255,255,255),
       bool cutExtension = false, const std::string &extension = ".ibm",
       EGUI_ALIGNMENT leftAlign = EGUIA_CENTER);
  ~Text() {}

  IGUIStaticText *guiTxt;

private:
};

#endif
