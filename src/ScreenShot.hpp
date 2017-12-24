/**
 * @Author: raph
 * @Date:   2017-06-18T00:24:48+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:46:44+02:00
 */

#ifndef SCREENSHOT_HPP
# define SCREENSHOT_HPP

#include "Indie.hpp"

class ScreenShot {
public:
	ScreenShot(const std::string &path);
	~ScreenShot();

  void takeScreenshot() const;
private:
  void loadScreenshot(const std::string &);

  c8 filename[64];
  IImage* image;
};

#endif
