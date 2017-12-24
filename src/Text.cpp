/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-25T13:19:26+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:43:48+02:00
 */

#include "Text.hpp"
#include "Core.hpp"

Text::Text(const std::string &txt, const rect<s32> &pos, int fontSize,
     SColor color, bool cutExtension, const std::string &extension,
     EGUI_ALIGNMENT align)
{
  std::wstring save;
  if (txt == "")
    return;

  if (cutExtension == true)
  {
    std::string cutter(txt.substr(0, txt.find(extension)));
    save = std::wstring(cutter.begin(), cutter.end());
  }
  else
    save = std::wstring(txt.begin(), txt.end());
  CGUITTFont* tt_font = CGUITTFont::createTTFont(Core::Display.env, MISC("Font.ttf"), fontSize);
  this->guiTxt = Core::Display.env->addStaticText(save.c_str(), pos);
  guiTxt->setOverrideFont(tt_font);
  guiTxt->setOverrideColor(color);
  guiTxt->setTextRestrainedInside(false);
  guiTxt->setTextAlignment(align, EGUIA_CENTER);
  tt_font->drop();
}
