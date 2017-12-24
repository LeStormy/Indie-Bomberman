/**
 * @Author: raph
 * @Date:   2017-06-13T10:56:18+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-17T16:35:05+02:00
 */

#ifndef STARTGAME_HPP
# define STARTGAME_HPP

#include "Indie.hpp"

class StartGame {
public:
  StartGame();
  ~StartGame();

  void update();
  void startTimer();

private:
  std::chrono::time_point<std::chrono::system_clock> startTime;
  std::chrono::duration<double> timer;
  IGUIImage *image;
  bool remove;
};

#endif
