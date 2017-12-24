/**
 * @Author: raph
 * @Date:   2017-06-07T18:23:31+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T02:48:05+02:00
 */

#include "MeshPathGetter.hpp"
#include "Core.hpp"

template <>
const path       MeshPathFromEnum::getMeshPath(const Indie::Entity type,
					       const Indie::Biome biome,
					       const int height)
{
  switch (type)
  {
    case Indie::BOMB_ENTITY:
      return (MESH("bomb.b3d"));
    case Indie::FROZENBOMB_ENTITY:
      return (MESH("IceBomb.b3d"));
    case Indie::OILBOMB_ENTITY:
      return (MESH("OilBomb.b3d"));
    case Indie::BOMBFREEZER_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::BOMBOILER_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::FLAME_ENTITY:
      return (MESH("TMPMiniBlock.3ds"));
    case Indie::OIL_ENTITY:
      return (MESH("OilPoodle.3ds"));
    case Indie::ICE_ENTITY:
      return (MESH("Ice.3ds"));
    case Indie::INVINCIBLE_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::SPIKE_ENTITY:
      return (MESH("TMPMiniBlock.3ds"));
    case Indie::TRAMPOLINE_ENTITY:
      return (MESH("TMPMiniBlock.3ds"));
    case Indie::FALL_ENTITY:
      return (MESH("FallBlock.b3d"));
    case Indie::UNBREAKABLE_BORDER_ENTITY:
      switch (biome) {
	case Indie::COUNTRYSIDE :
	  return (MESH("CountrySide/TileCountryBreakableStraw.3ds"));
	case Indie::VOLCANO :
	  return (MESH("Magma/UnbreakableBorder.3ds"));
	case Indie::DESERT :
	  return (MESH("Desert/Exterior.3ds"));
	case Indie::SNOWY :
	  return (MESH("Icelands/Exterior.3ds"));
	default :
	  return (MESH("RoundedCornerTile.3ds"));
      }
    case Indie::UNBREAKABLE_ENTITY: // TODO UNBREAKABLE_BORDER /!\*
      switch (biome) { // TODO : Change Default value
	case Indie::COUNTRYSIDE :
	  return (MESH("CountrySide/UnbreakableCountry.3ds"));
	case Indie::VOLCANO :
	  return (MESH("Magma/Unbreakable.3ds"));
	case Indie::DESERT :
	  return (MESH("Desert/Unbreakable.3ds"));
	case Indie::SNOWY :
	  return (MESH("Icelands/Unbreakable.3ds"));
	default :
	  return (MESH("RoundedCornerTile.3ds"));
      }
    case Indie::BREAKABLE_ENTITY:
      switch (biome) { // TODO : Change Default value
	case Indie::COUNTRYSIDE :
	  return (MESH("CountrySide/TileCountryBreakable.3ds"));
	case Indie::VOLCANO :
	  return (MESH("Magma/Breakable.3ds"));
	case Indie::DESERT :
	  return (MESH("Desert/Breakable.3ds"));
	case Indie::SNOWY :
	  return (MESH("Icelands/Breakable.3ds"));
	default :
	  return (MESH("RoundedCornerTile.3ds"));
      }
    case Indie::MAGNET_ENTITY:
      return (MESH("Magnet.3ds"));
    case Indie::STONE_ENTITY:
      return (MESH("TMPBlock.3ds"));
    case Indie::GROUND_ENTITY:
      switch (biome) { // TODO : Change Default value
	case Indie::COUNTRYSIDE :
	  switch (height) {
	    case 1 :
	      return (MESH("CountrySide/TileCountryBrick.3ds"));
	    default :
	      return (MESH("CountrySide/GroundGrass.3ds"));
	  }
	case Indie::VOLCANO :
	  switch (height) {
	    case 1 :
	      return (MESH("Magma/Stories.3ds"));
	    default :
	      return (MESH("Magma/Ground.3ds"));
	  }
	case Indie::DESERT :
	  switch (height) {
	    case 1 :
	      return (MESH("Desert/Stories.3ds"));
	    default :
	      return (MESH("Desert/Ground.3ds"));
	  }
	case Indie::SNOWY :
	  switch (height) {
	    case 1 :
	      return (MESH("Icelands/Stories.3ds"));
	    default :
	      return (MESH("Icelands/Ground.3ds"));
	  }
	default :
	  return (MESH("TMPBlock2.3ds"));
      }
    case Indie::POWERSPEED_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::POWERKICK_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::RANGEUP_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::RANGEDOWN_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::BOMBCUP_ENTITY:
      return (MESH("PowerUps.b3d"));
    case Indie::BOMBDOWN_ENTITY:
      return (MESH("PowerUps.b3d"));
    default:
      return (MESH("PowerUps.b3d"));
  }
}

template <>
const path       MeshPathFromEnum::getTexturePath(const Indie::Entity type,
						  const Indie::Biome biome,
						  const int height)
{
  switch (type)
  {
    case Indie::BOMB_ENTITY:
      return (MESHTXT("Bomb.TGA"));
    case Indie::FROZENBOMB_ENTITY:
      return (MESH("IceBomb.TGA"));
    case Indie::OILBOMB_ENTITY:
      return (MESH("OilTexture.png"));
    case Indie::FLAME_ENTITY:
      return (MESHTXT("TMPFlame.png"));
    case Indie::FALL_ENTITY:
      return (MESH("Rust.TGA"));
    case Indie::BREAKABLE_ENTITY:
    {
      switch (biome)
      { // TODO : Change Default value
	case Indie::COUNTRYSIDE :
	  return (MESH("CountrySide/Breakable.TGA"));
	case Indie::VOLCANO :
	  return (MESH("Magma/Breakable.TGA"));
	case Indie::DESERT :
	  return (MESH("Desert/Breakable.TGA"));
	case Indie::SNOWY :
	  return (MESH("Icelands/Breakable.TGA"));
	default :
	  return (MESHTXT("TMPBreak.png"));
      }
    }
    case Indie::UNBREAKABLE_ENTITY:
    {
      switch (biome)
      { // TODO : Change Default value
	case Indie::COUNTRYSIDE :
	  return (MESH("CountrySide/OakWood.TGA"));
	case Indie::VOLCANO :
	  return (MESH("Magma/Unbreakable.TGA"));
	case Indie::DESERT :
	  return (MESH("Desert/Unreakable.TGA"));
	case Indie::SNOWY :
	  return (MESH("Icelands/Unbreakable.TGA"));
	default :
	  return (MESHTXT("Steel.TGA"));
      }
    }
    case Indie::UNBREAKABLE_BORDER_ENTITY:
    {
      switch (biome)
      { // TODO : Change Default value
	case Indie::COUNTRYSIDE :
	  return (MESH("CountrySide/Exterior.TGA"));
	case Indie::VOLCANO :
	  return (MESH("Magma/Exterior.TGA"));
	case Indie::DESERT :
	  return (MESH("Desert/Exterior.TGA"));
	case Indie::SNOWY :
	  return (MESH("Icelands/Exterior.TGA"));
	default :
	  return (MESHTXT("Steel.TGA"));
      }
    }
    case Indie::TRAMPOLINE_ENTITY:
      return (MESHTXT("TMPTrampoline.png"));
    case Indie::SPIKE_ENTITY:
      return (MESHTXT("TMPSpike.png"));
    case Indie::GROUND_ENTITY:
    {
      switch (biome) { // TODO : Change Default value
	case Indie::COUNTRYSIDE :
	  switch (height)
	  {
	    case 1 :
	      return (MESH("CountrySide/Stories.TGA"));
	    default :
	      return (MESH("CountrySide/Ground.png"));
	  }
	case Indie::VOLCANO :
	  switch (height)
	  {
	    case 1 :
	      return (MESH("Magma/Stories.TGA"));
	    default :
	      return (MESH("Magma/Ground.TGA"));
	  }
	case Indie::DESERT :
	  switch (height)
	  {
	    case 1 :
	      return (MESH("Desert/Stories.TGA"));
	    default :
	      return (MESH("Desert/Ground.TGA"));
	  }
	case Indie::SNOWY :
	  switch (height)
	  {
	    case 1 :
	      return (MESH("Icelands/Stories.TGA"));
	    default :
	      return (MESH("Icelands/Ground.png"));
	  }
	default :
	  return (MESHTXT("Gravel.TGA"));
      }
    }
    case Indie::POWERSPEED_ENTITY:
      return (MESHTXT("SpeedPlus.png"));
    case Indie::OIL_ENTITY:
      return (MESHTXT("OilTexture.png"));
    case Indie::ICE_ENTITY:
      return (MESHTXT("SnowAndCrystal.TGA"));
    case Indie::STONE_ENTITY:
      return (MESHTXT("TMPIce.png"));
    case Indie::POWERKICK_ENTITY:
      return (MESHTXT("KickBonus.png"));
    case Indie::RANGEUP_ENTITY:
      return (MESHTXT("RangePlus.png"));
    case Indie::RANGEDOWN_ENTITY:
      return (MESHTXT("RangeMinus.png"));
    case Indie::BOMBCUP_ENTITY:
      return (MESHTXT("BombPlus.png"));
    case Indie::BOMBDOWN_ENTITY:
      return (MESHTXT("BombLess.png"));
    case Indie::BOMBFREEZER_ENTITY:
      return (IMAGE("IceBonus"));
    case Indie::BOMBOILER_ENTITY:
      return (MESHTXT("OilBonus.png"));
    case Indie::INVINCIBLE_ENTITY:
      return (MESHTXT("Invincible.png"));
    case Indie::MAGNET_ENTITY:
      return (MESHTXT("Magnet.png"));
    default:
    {
      return (MESHTXT("default.png"));
    }
  }
}

template <>
const path       MeshPathFromEnum::getMeshPath(const Indie::PlayerType type,
					       const Indie::Biome,
					       const int id)
{
  switch (type)
  {
    case Indie::HUMAN_PLAYER :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerOne.b3d"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerTwo.b3d"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerThree.b3d"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerFour.b3d"));
	default :
	  return (MESH("AnimPlayer.b3d"));
      }
    }
    case Indie::IA_PLAYER_EZ :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerOne.b3d"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerTwo.b3d"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerThree.b3d"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerFour.b3d"));
	default :
	  return (MESH("AnimPlayer.b3d"));
      }
    }
    case Indie::IA_PLAYER_MED :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerOne.b3d"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerTwo.b3d"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerThree.b3d"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerFour.b3d"));
	default :
	  return (MESH("AnimPlayer.b3d"));
      }
    }
    case Indie::IA_PLAYER_HARD :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerOne.b3d"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerTwo.b3d"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerThree.b3d"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerFour.b3d"));
	default :
	  return (MESH("AnimPlayer.b3d"));
      }
    }
    default:
      return (MESH("default.3ds"));
  }
}

template <>
const path       MeshPathFromEnum::getTexturePath(const Indie::PlayerType type,
						  const Indie::Biome,
						  const int id)
{
  switch (type)
  {
    case Indie::HUMAN_PLAYER :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerColorSetOne.png"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerColorSetTwo.png"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerColorSetThree.png"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerColorSetYellow.png"));
	default :
	  return (MESH("TMPPlayer.png"));
      }
    }
    case Indie::IA_PLAYER_EZ :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerColorSetOne.png"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerColorSetTwo.png"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerColorSetThree.png"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerColorSetYellow.png"));
	default :
	  return (MESH("TMPPlayer.png"));
      }
    }
    case Indie::IA_PLAYER_MED :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerColorSetOne.png"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerColorSetTwo.png"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerColorSetThree.png"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerColorSetYellow.png"));
	default :
	  return (MESH("TMPPlayer.png"));
      }
    }
    case Indie::IA_PLAYER_HARD :
    {
      switch (id)
      {
	case 0 :
	  return (MESH("PlayersTextures/PlayerBasic/PlayerColorSetOne.png"));
	case 1 :
	  return (MESH("PlayersTextures/PlayerDarker/PlayerColorSetTwo.png"));
	case 2 :
	  return (MESH("PlayersTextures/PlayerGreen/PlayerColorSetThree.png"));
	case 3 :
	  return (MESH("PlayersTextures/PlayerYellow/PlayerColorSetYellow.png"));
	default :
	  return (MESH("TMPPlayer.png"));
      }
    }
    default :
      return (MESHTXT("default.png"));
  }
}

template <>
const path       MeshPathFromEnum::getTexturePath(const Indie::EffectType type,
						  const Indie::Biome,
						  const int)
{
  switch (type)
  {
    case Indie::FULLALPHA_EFFECT:
      return (IMAGE("particAlpha"));
    case Indie::CLASSICSMOKE_EFFECT:
      return (IMAGE("particSmoke"));
    case Indie::FLAME_EFFECT:
      return (IMAGE("BrightFire"));
    case Indie::FROZENSMOKE_EFFECT:
      return (IMAGE("particSmoke"));
    case Indie::WIN_EFFECT:
      return (IMAGE("partic"));
    case Indie::ROTATION_EFFECT:
      return (IMAGE("particSmoke"));
    default:
      return (IMAGE("particSmoke"));
  }
}
