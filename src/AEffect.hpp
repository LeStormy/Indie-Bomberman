//
// Created by baptiste on 6/3/17.
//

#ifndef INDIESTUDIO_ABONUS_HPP
#define INDIESTUDIO_ABONUS_HPP

#include <memory>
#include "Indie.hpp"

class APlayer;
class AEntity;

class AEffect
{
protected:
  APlayer					*_player = nullptr;
  AEntity					*_entity = nullptr;
  float 					_timer;
  int 					        _id;
  Indie::EffectType 				_type;

public:
  virtual ~AEffect() {}

  virtual void 	update() = 0;

  static std::unique_ptr<AEffect>	createEffect(Indie::EffectType, APlayer *, int,
                                                std::pair<SColor, SColor> = {{255, 255, 255, 255},{255, 255, 255, 255}});
  static std::unique_ptr<AEffect>	createEffect(Indie::EffectType, AEntity *, int,
                                                std::pair<SColor, SColor> = {{255, 255, 255, 255},{255, 255, 255, 255}});

  bool				operator==(const Indie::EffectType type) { return _type == type; }
  void 				setId(const int id) { _id = id; }
};

#endif //INDIESTUDIO_ABONUS_HPP
