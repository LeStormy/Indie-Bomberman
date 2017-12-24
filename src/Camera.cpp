/**
 * @Author: raph
 * @Date:   2017-06-13T14:39:09+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T20:06:08+02:00
 */

#include "Core.hpp"
#include "Camera.hpp"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

CameraManager::CameraManager() : Camera(nullptr), effect(CameraManager::NOP), timer(0.0)
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::InitCam(const std::pair<size_t, size_t> &mapSize, bool splash)
{
  if (!splash)
  {
    this->Camera = Core::Display.smgr->addCameraSceneNode(0, {-10,-10,-10}, {-10,-10,-10});
    this->_origPos = vector3df(-10,-10,-10);
    this->_origTar = vector3df(static_cast<float>(mapSize.first) / 2.0f, 0.0f, static_cast<float>(mapSize.second) / 2.0f + 0.5f);
    this->_targetPos = vector3df(static_cast<float>(mapSize.first) / 2.0f, static_cast<float>(mapSize.second) - 1.0f, static_cast<float>((static_cast<float>(mapSize.second) / 2.0f) - (static_cast<float>(mapSize.second) / 2.0f) * cos(RAD(60))));
    this->_targetTar = vector3df(static_cast<float>(mapSize.first) / 2.0f, 0.0f, static_cast<float>(mapSize.second) / 2.0f + 0.5f);
  }
  else
  {
    this->Camera = Core::Display.smgr->addCameraSceneNode(0, {0,0,0}, {0,0,0});
    this->_origPos = vector3df(0,0,0);
    this->_origTar = vector3df(0,0,0);
    this->_targetPos = vector3df(0,-1,-2);
    this->_targetTar = vector3df(0,0.5,0);
  }
}

void CameraManager::PlaceGameCamera()
{
  this->Camera->setPosition(this->_targetPos);
  this->Camera->setTarget(this->_targetTar);
}

void CameraManager::cancelEffect()
{
  effect = CameraManager::NOP;
}

void CameraManager::SplashZoom(float length)
{
  if (effect != CameraManager::NOP)
    return ;
  this->timer = std::chrono::duration<double>::zero();
  this->startTime = std::chrono::system_clock::now();
  this->effect = CameraManager::ROTATE;
  this->length = length;
  this->_origPos = vector3df(0,20,-20);
  this->_origTar = vector3df(0,4,0);
  this->_targetPos = vector3df(0,2,-6);
  this->_targetTar = vector3df(0,4,0);
  this->Camera->setTarget(_origTar);
}

void CameraManager::AroundTheWorld(float length, const std::pair<size_t, size_t> &mapSize)
{
  if (effect != CameraManager::NOP)
    return ;
  this->timer = std::chrono::duration<double>::zero();
  this->startTime = std::chrono::system_clock::now();
  this->effect = CameraManager::ROTATE;
  this->length = length;
  this->Camera->setTarget(_origTar);
  this->_origPos = vector3df(-10, -10, -10);
  this->_origTar = vector3df(static_cast<float>(mapSize.first) / 2.0f, 0.0f, static_cast<float>(mapSize.second) / 2.0f + 0.5f);
  this->_targetPos = vector3df(static_cast<float>(mapSize.first) / 2.0f, static_cast<float>(mapSize.second) - 1.0f, static_cast<float>((static_cast<float>(mapSize.second) / 2.0f) - (static_cast<float>(mapSize.second) / 2.0f) * cos(RAD(60))));
  this->_targetTar = vector3df(static_cast<float>(mapSize.first) / 2.0f, 0.0f, static_cast<float>(mapSize.second) / 2.0f + 0.5f);
}

void CameraManager::ZoomOnPlayer(const vector3df &tar, Indie::Direction direction, float length)
{
  if (effect != CameraManager::NOP)
    return ;
  this->timer = std::chrono::duration<double>::zero();
  this->effect = CameraManager::ZOOMPLAYER;
  this->length = length;
  this->_origPos = this->Camera->getPosition();
  this->_origTar = this->Camera->getTarget();
  this->_targetTar = vector3df(tar.X, tar.Y + 1, tar.Z);
  switch (direction)
  {
    case Indie::UP_DIRECTION:
      this->_targetPos = vector3df(tar.X, tar.Y + 2, tar.Z + 2);
      break ;
    case Indie::DOWN_DIRECTION:
      this->_targetPos = vector3df(tar.X, tar.Y + 2, tar.Z - 2);
      break ;
    case Indie::LEFT_DIRECTION:
      this->_targetPos = vector3df(tar.X - 2, tar.Y + 2, tar.Z);
      break ;
    case Indie::RIGHT_DIRECTION:
      this->_targetPos = vector3df(tar.X + 2, tar.Y + 2, tar.Z);
      break ;
    default :
      this->_targetPos = vector3df(tar.X, tar.Y + 2, tar.Z - 2);
  }
}

void CameraManager::UpdateRotate(const std::pair<size_t, size_t> &)
{
  if (this->timer.count() == 0)
    this->startTime = std::chrono::system_clock::now();

  if (this->timer.count() <= length)
  {
    float count = static_cast<float>(this->timer.count());
    this->Camera->setPosition(vector3df(_targetPos.X - ((_targetPos.X - _origPos.X) * (1.0f - (count / length))),
                                        _targetPos.Y - ((_targetPos.Y - _origPos.Y) * (1.0f - (count / length))),
                                        _targetPos.Z - ((_targetPos.Z - _origPos.Z) * (1.0f - (count / length)))));
    this->Camera->setTarget(vector3df(_targetTar.X - ((_targetTar.X - _origTar.X) * (1.0f - (count / length))),
                                      _targetTar.Y - ((_targetTar.Y - _origTar.Y) * (1.0f - (count / length))),
                                      _targetTar.Z - ((_targetTar.Z - _origTar.Z) * (1.0f - (count / length)))));
  }
  else
    {
      this->Camera->setPosition(vector3df(_targetPos));
      this->Camera->setTarget(vector3df(_targetTar));
      this->effect = CameraManager::NOP;
    }
    this->timer = Core::Time - this->startTime;
}

void CameraManager::UpdateZoom(const std::pair<size_t, size_t> &)
{
  if (this->timer.count() == 0)
    this->startTime = std::chrono::system_clock::now();
  if (this->timer.count() < length)
  {
    float count = static_cast<float>(this->timer.count());
    this->Camera->setPosition(vector3df(_targetPos.X - ((_targetPos.X - _origPos.X) * (1.0f - (count / length))),
                                        _targetPos.Y - ((_targetPos.Y - _origPos.Y) * (1.0f - (count / length))),
                                        _targetPos.Z - ((_targetPos.Z - _origPos.Z) * (1.0f - (count / length)))));
    this->Camera->setTarget(vector3df(_targetTar.X - ((_targetTar.X - _origTar.X) * (1.0f - (count / length))),
                                      _targetTar.Y - ((_targetTar.Y - _origTar.Y) * (1.0f - (count / length))),
                                      _targetTar.Z - ((_targetTar.Z - _origTar.Z) * (1.0f - (count / length)))));

  }
  else
    {
      this->Camera->setPosition(this->_targetPos);
      this->Camera->setTarget(this->_targetTar);
      this->effect = CameraManager::NOP;
    }
    this->timer = Core::Time - this->startTime;
}


void CameraManager::Update(const std::pair<size_t, size_t> &mapSize)
{
  if (this->effect == CameraManager::NOP)
    return ;
  switch (this->effect)
  {
    case CameraManager::ROTATE:
      UpdateRotate(mapSize);
      break;
    case CameraManager::ZOOMPLAYER:
      UpdateZoom(mapSize);
      break;
    default:;
  }
}
