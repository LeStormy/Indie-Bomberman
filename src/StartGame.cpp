/**
 * @Author: raph
 * @Date:   2017-06-13T10:56:09+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-17T18:08:08+02:00
 */

#include <chrono>
#include <cmath>
#include "StartGame.hpp"
#include "Core.hpp"

StartGame::StartGame() : remove(false)
{

}

StartGame::~StartGame()
{

}

void StartGame::startTimer()
{
	this->timer = std::chrono::duration<double>::zero();
}

void StartGame::update()
{
	if (static_cast<int>(3 - std::floor(this->timer.count())) > 3);
  else if (this->timer.count() < 3)
  {
		if (this->timer.count() == 0)
		{
			this->startTime = std::chrono::system_clock::now();
			image = Core::Display.env->addImage(rect<s32>(710, 290, 710 + 0, 790));
			image->setImage(Core::Display.driver->getTexture(IMAGE("3")));
			image->setUseAlphaChannel(true);
			Core::Sound.stopAll();
			Core::Sound.playMusic(AUDIO("StartJingle"), false);
		}
		else if (static_cast<int>(3 - std::floor(this->timer.count())) != static_cast<int>(3 - std::floor(this->timer.count() + Core::frameRate) - 1))
		{
			image->remove();
			image = Core::Display.env->addImage(rect<s32>(710, 290, 710 + 500, 790));
			image->setImage(Core::Display.driver->getTexture(IMAGE(std::to_string(static_cast<int>(3 - std::floor(this->timer.count()))))));
		}
    remove = true;
  }
  else if (this->timer.count() > 3 && remove == true)
  {
    image->remove();
		image = Core::Display.env->addImage(rect<s32>(710, 290, 710 + 500, 790));
		image->setImage(Core::Display.driver->getTexture(IMAGE("Go")));
		remove = false;
  }
  if (this->timer.count() >= 5.3 && Core::Sound.MainAudio.getStatus() != sf::SoundSource::Playing)
    DisplayEngine::dSwitch = Indie::TO_GAME;
	this->timer = Core::Time - this->startTime;
}
