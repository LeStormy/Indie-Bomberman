/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-28T11:41:46+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T22:26:53+02:00
 */

#include "MenuScreens.hpp"
#include "Directory.hpp"

bool SetGameScreen::customMap = true;
char SetGameScreen::isChangingName = -1;
int8_t SetGameScreen::premadeSize = 0;
int8_t SetGameScreen::premadeIndex = 0;

SetGameScreen::SetGameScreen() {

}

void SetGameScreen::setPlayers(const Settings &settings)
{
  io::path iaEzPressedPath(IMAGE("IAEZButtonPressed"));
  io::path iaMedPressedPath(IMAGE("IAMEDButtonPressed"));
  io::path iaHardPressedPath(IMAGE("IAHARDButtonPressed"));
  io::path humanPressedPath(IMAGE("HumanButtonPressed"));
  io::path unusedPressedPath(IMAGE("UnusedButtonPressed"));

/* Players Settings */
  /* Player One */
  IGUIImage *Icon = Core::Display.env->addImage(rect<s32>(X(2)-100, Y(1.5), X(2) + 300, Y(1.5) + 300));
  Icon->setImage(Core::Display.driver->getTexture(IMAGE("Player1")));
  Icon->setScaleImage(true);
  Text NameTxt1(settings.players[0].name, rect<s32>(X(2)-100, Y(1.5) + 300, X(2) + 300, Y(1.5) + 350), 50);
  Button ChangeName1(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                     rect<s32>(X(2)-100, Y(1.5) + 300, X(2) + 300, Y(1.5) + 350), Indie::MenuButtons::CHANGENAME1_BUTTON);

  /* Player Two */
  Icon = Core::Display.env->addImage(rect<s32>(X(6.5) - 100, Y(1.5), X(6.5) + 300, Y(1.5) + 300));
  Icon->setImage(Core::Display.driver->getTexture(IMAGE("Player2")));
  Icon->setScaleImage(true);
  Text NameTxt2(settings.players[1].name, rect<s32>(X(6.5) - 100, Y(1.5) + 300, X(6.5) + 300, Y(1.5) + 350), 50);
  Button ChangeName2(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                     rect<s32>(X(6.5) - 100, Y(1.5) + 300, X(6.5) + 300, Y(1.5) + 350), Indie::MenuButtons::CHANGENAME2_BUTTON);

  /* Player Three */
  Icon = Core::Display.env->addImage(rect<s32>(X(13.5) - 300, Y(1.5), X(13.5) + 100, Y(1.5) + 300));
  Icon->setImage(Core::Display.driver->getTexture(IMAGE("Player3")));
  Icon->setScaleImage(true);
  Text NameTxt3(settings.players[2].name, rect<s32>(X(13.5) - 300, Y(1.5) + 300, X(13.5) + 100, Y(1.5) + 350), 50);
  Button ChangeName3(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                     rect<s32>(X(13.5) - 300, Y(1.5) + 300, X(13.5) + 100, Y(1.5) + 350), Indie::MenuButtons::CHANGENAME3_BUTTON);

  /* Player Four */
  Icon = Core::Display.env->addImage(rect<s32>(X(18) - 300, Y(1.5), X(18) + 100, Y(1.5) + 300));
  Icon->setImage(Core::Display.driver->getTexture(IMAGE("Player4")));
  Icon->setScaleImage(true);
  Text NameTxt4(settings.players[3].name, rect<s32>(X(18) - 300, Y(1.5) + 300, X(18) + 100, Y(1.5) + 350), 50);
  Button ChangeName4(IMAGE("KeyBar"), IMAGE("KeyBarPressed"),
                     rect<s32>(X(18) - 300, Y(1.5) + 300, X(18) + 100, Y(1.5) + 350), Indie::MenuButtons::CHANGENAME4_BUTTON);


  std::array<Indie::MenuButtons, 4> buttonId = {Indie::MenuButtons::TYPE1_BUTTON, Indie::MenuButtons::TYPE2_BUTTON, Indie::MenuButtons::TYPE3_BUTTON, Indie::MenuButtons::TYPE4_BUTTON};
  std::array<rect<s32>, 4> buttonPos = {rect<s32>(X(2)-100, Y(1.5), X(2) + 300, Y(1.5) + 50),
                                        rect<s32>(X(6.5) - 100, Y(1.5), X(6.5) + 300, Y(1.5)+50),
                                        rect<s32>(X(13.5) - 300, Y(1.5), X(13.5) + 100, Y(1.5)+50),
                                        rect<s32>(X(18) - 300, Y(1.5), X(18) + 100, Y(1.5)+50)};
   /* Player Types */
  for (uint8_t i = 0 ; i < 4; i++)
  {
    switch (settings.players[i].playerType) {
      case Indie::IA_PLAYER_HARD:
        Button(iaHardPressedPath, iaHardPressedPath, buttonPos[i], buttonId[i]);
        break ;
      case Indie::IA_PLAYER_MED:
        Button(iaMedPressedPath, iaMedPressedPath, buttonPos[i], buttonId[i]);
        break ;
      case Indie::IA_PLAYER_EZ:
        Button(iaEzPressedPath, iaEzPressedPath, buttonPos[i], buttonId[i]);
        break ;
      case Indie::UNUSED_PLAYER:
        Button(unusedPressedPath, unusedPressedPath, buttonPos[i], buttonId[i]);
        break ;
      case Indie::HUMAN_PLAYER:
        Button(humanPressedPath, humanPressedPath, buttonPos[i], buttonId[i]);
        break ;
      }
    }
}

void SetGameScreen::setCustom(const Settings &)
{
  io::path minus(IMAGE("MinusButton"));
  io::path minusPressed(IMAGE("MinusButtonPressed"));
  io::path plus(IMAGE("PlusButton"));
  io::path plusPressed(IMAGE("PlusButtonPressed"));

  Button MapWidthLess(minus, minusPressed, rect<s32>(X(1), Y(5), X(1.75), Y(5.75)), Indie::MenuButtons::MWIDTH_BUTTON);
  Button MapWidthPlus(plus, plusPressed, rect<s32>(X(3.25), Y(5), X(4), Y(5.75)), Indie::MenuButtons::PWIDTH_BUTTON);
  Button MapHeightLess(minus, minusPressed, rect<s32>(X(4), Y(5), X(4.75), Y(5.75)), Indie::MenuButtons::MHEIGHT_BUTTON);
  Button MapHeightPlus(plus, plusPressed, rect<s32>(X(6.25), Y(5), X(7), Y(5.75)), Indie::MenuButtons::PHEIGHT_BUTTON);

  Button PrevBiome(IMAGE("LeftArrow"), IMAGE("LeftArrowPressed"),
                          rect<s32>(X(1), Y(6), X(1.75), Y(6.90)), Indie::MenuButtons::PREVBIOME_BUTTON);
  Button NextBiome(IMAGE("RightArrow"), IMAGE("RightArrowPressed"),
                          rect<s32>(X(6.25), Y(6), X(7), Y(6.90)), Indie::MenuButtons::NEXTBIOME_BUTTON);

  Button PlatformsPrev(IMAGE("LeftArrow"), IMAGE("LeftArrowPressed"),
                      rect<s32>(X(1), Y(7.25), X(1.75), Y(8)), Indie::MenuButtons::PLATFORM_BUTTON);
  Button PlatformsNext(IMAGE("RightArrow"), IMAGE("RightArrowPressed"),
                      rect<s32>(X(6.25), Y(7.25), X(7), Y(8)), Indie::MenuButtons::PLATFORM_BUTTON);
  Button Reroll(IMAGE("RerollButton"), IMAGE("RerollButtonPressed"),
                  rect<s32>(X(1) + 50, Y(8), X(7) - 50, Y(9)), Indie::MenuButtons::REROLL_BUTTON);
}

void SetGameScreen::setPremade(const Settings &)
{
  Button prevMap(IMAGE("LeftArrow"), IMAGE("LeftArrowPressed"),
                  rect<s32>(X(19) - 700, Y(5) + 150, X(19) - 600, Y(5) + 250), Indie::MenuButtons::PREVMAP_BUTTON);
  Button nextMap(IMAGE("RightArrow"), IMAGE("RightArrowPressed"),
                  rect<s32>(X(19), Y(5) + 150, X(19) + 100, Y(5) + 250), Indie::MenuButtons::NEXTMAP_BUTTON);
}

void SetGameScreen::setMap(const Settings &settings)
{
  if (SetGameScreen::customMap == true)
  {
    IGUIImage *MapImg = Core::Display.env->addImage(rect<s32>(X(19) - 600, Y(5), X(19), Y(9)));
    MapImg->setImage(Core::Display.driver->getTexture(IMAGE("Custom" + std::to_string(settings.mapSet.Biome))));
    Button Premade(IMAGE("GameMaps"), IMAGE("GameMapsPressed"),
                    rect<s32>(X(8), Y(5.5), X(12), Y(6.2)), Indie::MenuButtons::PREMADE_BUTTON);
    Button Custom(IMAGE("CustoMapPressed"), IMAGE("CustoMapPressed"),
                      rect<s32>(X(8), Y(7.7), X(12), Y(8.4)), Indie::MenuButtons::CUSTOM_BUTTON);
    IGUIImage *BgFilter = Core::Display.env->addImage(rect<s32>(X(1), Y(5), X(7), Y(9)));
    BgFilter->setImage(Core::Display.driver->getTexture(IMAGE("DarkFilter")));
    Text("Custom", rect<s32>(X(8), Y(6.5), X(12), Y(7.5)), 50);
  }
  this->setCustom(settings);
  if (SetGameScreen::customMap == false)
  {
    if (MapPreview.size() != 0)
    {
      if (SetGameScreen::premadeIndex < 0)
        SetGameScreen::premadeIndex = static_cast<int8_t>(MapPreview.size()) - 1;
      else if (SetGameScreen::premadeIndex >= static_cast<int8_t>(MapPreview.size()))
        SetGameScreen::premadeIndex = 0;
      this->setPremade(settings);
      IGUIImage *MapImg = Core::Display.env->addImage(rect<s32>(X(19) - 600, Y(5), X(19), Y(9)));
      io::path MapsDir(CONF("Maps/"));
      io::path extension(".png");
      io::path mapPath(MapsDir + MapPreview[SetGameScreen::premadeIndex].c_str() + extension);
      MapImg->setImage(Core::Display.driver->getTexture(mapPath));
      MapImg->setScaleImage(true);
      Text(MapPreview[SetGameScreen::premadeIndex].c_str(), rect<s32>(X(8), Y(6.5), X(12), Y(7.5)), 50);
    }
    Button Premade(IMAGE("GameMapsPressed"), IMAGE("GameMapsPressed"),
                    rect<s32>(X(8), Y(5.5), X(12), Y(6.2)), Indie::MenuButtons::PREMADE_BUTTON);
    Button Custom(IMAGE("CustoMap"), IMAGE("CustoMapPressed"),
                      rect<s32>(X(8), Y(7.7), X(12), Y(8.4)), Indie::MenuButtons::CUSTOM_BUTTON);
    IGUIImage *BgFilter = Core::Display.env->addImage(rect<s32>(X(1), Y(5), X(7), Y(9)));
    BgFilter->setImage(Core::Display.driver->getTexture(IMAGE("DarkFilter")));
  }

  Text("W:" + std::to_string(settings.mapSet.mapSize.first - 2), rect<s32>(X(2),Y(5.2),X(3),Y(5.55)), 30);
  Text("H:" + std::to_string(settings.mapSet.mapSize.second - 2), rect<s32>(X(5),Y(5.2),X(6),Y(5.55)), 30);

  IGUIImage *Biome = Core::Display.env->addImage(rect<s32>(X(2), Y(5.95), X(6), Y(7.05)));
  Biome->setImage(Core::Display.driver->getTexture(IMAGE("Biome" + std::to_string(static_cast<int>(settings.mapSet.Biome)))));

  if (settings.mapSet.platforms)
    Text("Platforms", rect<s32>(X(2), Y(7.45), X(6), Y(7.8)), 30);
  else
    Text("No Platforms", rect<s32>(X(2), Y(7.45), X(6), Y(7.8)), 30);
}

void SetGameScreen::sceneSetter(const Settings &settings)
{
  ITexture* image = Core::Display.driver->getTexture(IMAGE("NewBackground"));
  Core::Display.env->addImage(image, position2d<int>(0,0));

  Directory dir;

  this->MapPreview = dir.getFiles(".map", CONF("Maps/"), false);

  SetGameScreen::premadeSize = static_cast<int8_t>(MapPreview.size()) - 1;

/* GUI Elements */
  Button Start(IMAGE("StartButton"), IMAGE("StartButtonPressed"),
              rect<s32>(X(6),Y(9.4),X(9),Y(9.9)), Indie::MenuButtons::OUTOFMENU_BUTTON);
  Button Back(IMAGE("BackButton"), IMAGE("BackButtonPressed"),
              rect<s32>(X(11),Y(9.4),X(14),Y(9.9)), Indie::MenuButtons::MAINPAGE_BUTTON);


  this->setPlayers(settings);
  this->setMap(settings);
}
