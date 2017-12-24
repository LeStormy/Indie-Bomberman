/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-18T14:49:20+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-14T18:05:37+02:00
 */

#ifndef SOUNDENGINE_HPP_
# define SOUNDENGINE_HPP_

#include <SFML/Audio.hpp>
#include "Settings.hpp"

class SoundEngine {
public:
  SoundEngine() : Sets({100,100,100,false}) {}
  ~SoundEngine() {}

  void playMusic(const std::string &soundPath, bool loop = true);
  void playSound(const std::string &soundPath);
  void updateVolume();
  void stopAll();

  sf::Music MainAudio;
  std::array<sf::Music, 32> SoundEffectChannels;

  SoundSets Sets;

private:

};

#endif
