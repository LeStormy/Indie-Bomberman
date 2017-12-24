/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-27T18:02:39+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T22:26:11+02:00
 */

#include "SoundEngine.hpp"
#include "MenuScreens.hpp"

void SoundEngine::playMusic(const std::string &soundPath, bool loop) {
  if (this->Sets.Mute == false)
  {
    this->updateVolume();
    if (!this->MainAudio.openFromFile(soundPath))
      return ;
    this->MainAudio.setVolume(this->Sets.MusicVolume * (static_cast<float>(this->Sets.MasterVolume) / 100));
    this->MainAudio.setLoop(loop);
    this->MainAudio.play();
  }
}

void SoundEngine::playSound(const std::string &soundPath) {
  if (this->Sets.Mute == false)
  {
    this->updateVolume();
    for (auto & it : this->SoundEffectChannels)
      if (it.getStatus() != sf::SoundSource::Playing)
      {
        if (!it.openFromFile(soundPath))
          return ;
        it.setVolume(this->Sets.FXVolume * (static_cast<float>(this->Sets.MasterVolume) / 100));
        it.play();
        break;
      }
  }
}

void SoundEngine::updateVolume()
{
  this->MainAudio.setVolume(this->Sets.MusicVolume * (static_cast<float>(this->Sets.MasterVolume) / 100));
  for (auto & it : this->SoundEffectChannels)
    it.setVolume(this->Sets.FXVolume * (static_cast<float>(this->Sets.MasterVolume) / 100));
}

void SoundEngine::stopAll() {
  this->MainAudio.stop();
  for (auto & it : this->SoundEffectChannels)
    it.stop();
}
