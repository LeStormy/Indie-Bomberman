/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-22T17:46:04+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T22:26:06+02:00
 */

#include "ErrorMessage.hpp"
#include "MenuScreens.hpp"

void APopUp::init(const std::string &message, bool okButton, bool dismissButton, const io::path &filterTex)
{
 ITexture* image = Core::Display.driver->getTexture(filterTex);
 Core::Display.env->addImage(image, position2d<int>(0,0));
 Text(message, rect<s32>(700, 350, 1300, 700), 30, SColor(255,255,255,255));
 if (okButton)
   Button(IMAGE("BackButton"), IMAGE("BackButtonPressed"), rect<s32>(750, 900, 950, 1000), Indie::OK_BUTTON);
 if (dismissButton)
   Button(IMAGE("BackButton"), IMAGE("BackButtonPressed"), rect<s32>(1050, 900, 1250, 1000), Indie::DISMISS_BUTTON);
}
