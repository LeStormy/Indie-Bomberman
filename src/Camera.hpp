/**
 * @Author: raph
 * @Date:   2017-06-13T14:39:17+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:32:09+02:00
 */

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <chrono>
#include "Indie.hpp"

class CameraManager {
public:
  CameraManager();
  ~CameraManager();

  void PlaceGameCamera();
  void ZoomOnPlayer(const vector3df &pos, Indie::Direction direction, float length = 3.0);
  void InitCam(const std::pair<size_t, size_t> &mapSize, bool splash = false);
  void AroundTheWorld(float length, const std::pair<size_t, size_t> &mapSize);
  void SplashZoom(float length);
  void Update(const std::pair<size_t, size_t> &mapSize);
  void UpdateRotate(const std::pair<size_t, size_t> &mapSize);
  void UpdateZoom(const std::pair<size_t, size_t> &mapSize);
  void cancelEffect();

  ICameraSceneNode *Camera;

  enum Effect {
    NOP,
    ROTATE,
    ZOOMPLAYER
  };

private:
//  float timer;
  Effect effect;
  float length;
  vector3df _origPos;
  vector3df _origTar;
  vector3df _targetPos;
  vector3df _targetTar;
  std::chrono::time_point<std::chrono::system_clock> startTime;
  std::chrono::duration<double> timer;
};

#endif
