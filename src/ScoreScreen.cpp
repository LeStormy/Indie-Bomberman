/**
 * @Author: raph
 * @Date:   2017-06-07T13:37:18+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:49:22+02:00
 */


#include "Loader.hpp"
#include "MenuScreens.hpp"

ScoreScreen::ScoreScreen()
{
  LoadSave loader;

  loader.loadScores(CONF("LeaderBoard.conf"), this->_allScores);
  std::sort(this->_allScores[Indie::ScoreType::CLASSIC].begin(), this->_allScores[Indie::ScoreType::CLASSIC].end(), [](auto &left, auto &right) {
	  return left.second < right.second;
  });
}

void ScoreScreen::sceneSetter(const Settings &)
{
	ITexture* image = Core::Display.driver->getTexture(IMAGE("ScoreBackground"));
	Core::Display.env->addImage(image, position2d<int>(0, 0));
  /* GUI Elements */
  Button Back(IMAGE("BackButton"), IMAGE("BackButtonPressed"),
	      rect<s32>(X(8.5),Y(9.4),X(11.5),Y(9.9)), Indie::MenuButtons::MAINPAGE_BUTTON);

  for (size_t i = 0; i < 10 && i < this->_allScores[Indie::ScoreType::CLASSIC].size(); i++)
  {
	  Text txt(this->_allScores[Indie::ScoreType::CLASSIC][i].first, rect<s32>(150, 200 + (i * 50), 1600, 250 + (i * 50)), 50, SColor(255, 255, 255, 255), true, ".ibm", EGUIA_UPPERLEFT);
	  Text txtscore(std::to_string(this->_allScores[Indie::ScoreType::CLASSIC][i].second), rect<s32>(1600, 200 + (i * 50), 1900, 250 + (i * 50)), 50, SColor(255, 255, 255, 255), false, "", EGUIA_UPPERLEFT);
  }
}
