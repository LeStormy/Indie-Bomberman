/**
 * @Author: raph
 * @Date:   2017-06-12T15:05:40+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T04:04:11+02:00
 */

#ifndef GAMEOVER_HPP
# define GAMEOVER_HPP

#include "Text.hpp"
#include "APlayer.hpp"

class GameOver {
public:
  GameOver();
  ~GameOver();

  bool isEnd(const std::array<PlayerSet, 4> & players) const;
  void update();

  void setWinner(const std::array<PlayerSet, 4> &players);
  int getWinner() const;
  void startTimer();

private:
  int winner;
  float timer;
  IGUIImage *image;
  bool start;
  bool remove;
};

#endif
