/**
 * @Author: raph
 * @Date:   2017-06-17T23:43:54+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:46:38+02:00
 */

#include "ScreenShot.hpp"
#include "Core.hpp"

ScreenShot::ScreenShot(const std::string &path)
{
	this->loadScreenshot(path);
}

ScreenShot::~ScreenShot()
{
	image->drop();
}

void ScreenShot::takeScreenshot() const
{
	if (image)
		Core::Display.driver->writeImageToFile(image, filename);
}

void ScreenShot::loadScreenshot(const std::string &path)
{
	image = Core::Display.driver->createScreenShot();
	if (image)
		snprintf(filename, 64, "%s.png", path.c_str());
}
