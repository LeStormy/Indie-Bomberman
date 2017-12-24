/**
 * @Author: raph
 * @Date:   2017-06-15T14:18:32+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-15T14:31:08+02:00
 */

#include "AEffect.hpp"
#include "SpeedUpEffect.hpp"
#include "SmokeEffect.hpp"
#include "PowerUpsEffects.hpp"
#include "KickEffect.hpp"
#include "WinEffect.hpp"
#include "RotationEffect.hpp"
#include "FlameEffect.hpp"

std::unique_ptr<AEffect>	AEffect::createEffect(Indie::EffectType bType, APlayer *ply, int id, std::pair<SColor, SColor> colorEffect)
{
  switch (bType) {
    case Indie::SPEED_EFFECT:
      return (std::make_unique<SpeedUpEffect>(ply, id));
    case Indie::KICK_EFFECT:
      return (std::make_unique<KickEffect>(ply, id));
    case Indie::INVINCIBLE_EFFECT:
      return (std::make_unique<InvincibleEffect>(ply, id));
    case Indie::OIL_EFFECT:
      return (std::make_unique<OilEffect>(ply, id));
    case Indie::ICE_EFFECT:
      return (std::make_unique<IceEffect>(ply, id));
    case Indie::WIN_EFFECT:
      return (std::make_unique<WinEffect>(ply, colorEffect, id));
    case Indie::CLASSICSMOKE_EFFECT:
      return (std::make_unique<SmokeEffect>(bType, ply, colorEffect, id));
    default :
      throw std::runtime_error("Invalid Class try to be generated");
  }
}

std::unique_ptr<AEffect>	AEffect::createEffect(Indie::EffectType bType, AEntity *entity, int id, std::pair<SColor, SColor> colorEffect)
{
  switch (bType) {
    case Indie::FLAME_EFFECT:
      return (std::make_unique<FlameEffect>(bType, entity, id, colorEffect));
    case Indie::CLASSICSMOKE_EFFECT:
      return (std::make_unique<SmokeEffect>(bType, entity, colorEffect, id));
    case Indie::FROZENSMOKE_EFFECT:
      return (std::make_unique<SmokeEffect>(bType, entity, colorEffect, id));
    case Indie::ROTATION_EFFECT:
      return (std::make_unique<RotationEffect>(bType, entity, colorEffect, id));
    default :
      throw std::runtime_error("Invalid Class try to be generated");
  }
}
