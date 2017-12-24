/**
 * @Author: raph
 * @Date:   2017-06-12T15:04:35+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T21:10:50+02:00
 */

#include "GameOver.hpp"
#include "Core.hpp"
#include "MenuScreens.hpp"

GameOver::GameOver() : winner(-1), image(nullptr), start(true), remove(false)
{

}

GameOver::~GameOver()
{

}

bool GameOver::isEnd(const std::array<PlayerSet, 4> &players) const
{
  char alives = 0;
  for (size_t i = 0; i < 4; i++)
    if (players[i].playerType != Indie::UNUSED_PLAYER && players[i].alive == true)
      ++alives;
  if (alives > 1)
    return false;
  return true;
}

void GameOver::setWinner(const std::array<PlayerSet, 4> &players)
{
  char alive = -1;
  for (char i = 0; i < 4; i++)
    if (players[i].playerType != Indie::UNUSED_PLAYER && players[i].alive == true)
      alive = i + 1;
  if (alive == -1)
    this->winner = 0;
  else
  {
    this->winner = alive;
    ScoreMap board;
    LoadSave loader;
    loader.loadScores(CONF("LeaderBoard.conf"), board);
    bool addMe = false;
    for (auto & it : board[Indie::CLASSIC])
      if (players[winner - 1].score > it.second)
      {
        addMe = true;
        break ;
      }
    std::sort(board[Indie::ScoreType::CLASSIC].begin(), board[Indie::ScoreType::CLASSIC].end(), [](auto &left, auto &right) {
        return left.second < right.second;
      });
    std::string name = players[winner - 1].name;
    size_t score = players[winner - 1].score;
    if (board.size() < 10)
      board[Indie::ScoreType::CLASSIC].push_back(std::pair<std::string, size_t>(name, score));
    else if (addMe == true)
    {
      board[Indie::ScoreType::CLASSIC].at(9).first = name;
      board[Indie::ScoreType::CLASSIC].at(9).second = score;
    }
    loader.saveScores(CONF("LeaderBoard.conf"), board);
  }
}

void GameOver::startTimer()
{
  this->timer = 0;
}

int GameOver::getWinner() const
{
  return (this->winner);
}

void GameOver::update()
{
  if (timer >= 6.0 && Core::Sound.MainAudio.getStatus() != sf::SoundSource::Playing)
  {
    Core::Sound.stopAll();
    Core::Sound.playMusic(AUDIO("EndGameMusic"));
    if (start == true)
    {
      Button Start(IMAGE("StartButton"), IMAGE("StartButtonPressed"),
                  rect<s32>(X(6),Y(8),X(9),Y(9)), Indie::OUTOFMENU_BUTTON);
      Button Back(IMAGE("BackButton"), IMAGE("BackButtonPressed"),
                  rect<s32>(X(11),Y(8),X(14),Y(9)), Indie::SETGAME_BUTTON);
    }
    start = false;
  }
  if (this->timer >= 4)
  {
    if (timer <= 4.2)
    {
      if (remove == true)
        image->remove();
      image = Core::Display.env->addImage(rect<s32>(360, 150, 360 + static_cast<int>(1200 * ((timer - 4) * 5)), 333));
      if (winner == 0)
        image->setImage(Core::Display.driver->getTexture(IMAGE("Draw")));
      else
        image->setImage(Core::Display.driver->getTexture(IMAGE("Winner" + std::to_string(winner))));
      remove = true;
      image->setUseAlphaChannel(true);
    }
  }
  timer += Core::frameRate;
}
