cmake_minimum_required(VERSION 3.6)
project(indie)


set(PROJECT_SOURCE_DIR ".")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

include_directories("${PROJECT_SOURCE_DIR}/winInc")

if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS}")
else()
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -L../winInc")
endif()

set(SOURCE_FILES
        ./src/MapHandler.cpp
        ./src/PlayersManager.hpp
        ./src/APlayer.hpp
        src/AEntity.hpp
        src/AEntity.cpp
        src/PlayerIA.hpp
        src/PlayerIA.cpp
        ./src/PlayerHuman.hpp
        ./src/Settings.hpp
        ./src/Tile.cpp
        ./src/Tile.hpp
        src/Indie.hpp
        ./src/Input.cpp
        ./src/Input.hpp
        ./src/main.cpp
        ./src/MeshPathGetter.cpp
        ./src/MeshPathGetter.hpp
        ./src/MapHandler.hpp
        ./src/APlayer.cpp
        ./src/Binds.hpp
        ./src/Core.cpp
        ./src/Core.hpp
        ./src/MenuScreens.cpp
        ./src/MenuScreens.hpp
        ./src/Directory.cpp
        ./src/Directory.hpp
        ./src/DisplayEngine.cpp
        ./src/DisplayEngine.hpp
        ./src/IScreen.hpp
        ./src/Loader.cpp
        ./src/Loader.hpp
        ./src/Menu.cpp
        ./src/Menu.hpp
        ./src/MenuEventReceiver.hpp
        ./src/MenuEventReceiver.cpp
        ./src/OptionsMenu.cpp
        ./src/SetGameScreen.cpp
        ./src/SoundEngine.hpp
        ./src/SoundEngine.cpp
        ./src/CGUITTFont.cpp
        ./src/CGUITTFont.h
        ./src/ErrorMessage.cpp
        ./src/ErrorMessage.hpp
        ./src/PlayerHuman.cpp
        ./src/HudSet.cpp
        ./src/HudSet.hpp
        ./src/Text.hpp
        ./src/Text.cpp
        ./src/ProceduralGeneration.cpp
        ./src/ProceduralGeneration.hpp
        ./src/ProceduralUnbreakable.cpp
        ./src/ProceduralPlatform.cpp
        ./src/ScoreScreen.cpp
        ./src/HashType.hpp
        ./src/SpeedUpEffect.hpp
        ./src/AEffect.cpp
        ./src/GrassEntity.hpp
        ./src/BombEntity.hpp
        ./src/UnbreakableEntity.hpp
        ./src/IceEntity.hpp
        ./src/IceMalus.hpp
        ./src/FlameEntity.hpp
        ./src/MovementManager.hpp
        ./src/MovementManager.cpp
        ./src/StrafeMovement.hpp
        src/JumpMovement.hpp
        src/JumpMovement.cpp
        src/StrafeMovement.cpp
        ./src/PlayersManager.cpp
        ./src/BombEntity.cpp
        ./src/SpikeEntity.cpp
        ./src/FlameEntity.cpp
        ./src/FallEntity.cpp
        ./src/FallEntity.hpp
        ./src/TrampolineEntity.cpp
        ./src/PauseEventReceiver.cpp
        ./src/PauseEventReceiver.hpp
        ./src/InGameMenu.cpp
        ./src/InGameMenu.hpp
        ./src/KickEffect.hpp
        src/PowerEntity.hpp
        ./src/MagnetEntity.cpp
        ./src/MagnetEntity.hpp
        ./src/GameOver.cpp
        ./src/GameOver.hpp
        ./src/Light.cpp
        ./src/Light.hpp
        ./src/StartGame.cpp
        ./src/StartGame.hpp
        ./src/Camera.cpp
        ./src/Camera.hpp
        src/FrozenBombEntity.hpp
        src/FrozenBombEntity.cpp
        src/PowerUpsEffects.hpp
        src/OilBombEntity.cpp
        src/OilBombEntity.hpp
        src/IA_Scan.cpp
		src/SmokeEffect.hpp
        src/WinEffect.hpp
        src/RotationEffect.hpp
        src/FlameEffect.hpp
        src/ScreenShot.cpp
        src/ScreenShot.hpp
        src/FileChecker.cpp
        src/FileChecker.hpp
        )

if(MSVC)
	set(CMAKE_SUPPRESS_REGENERATION true)
	add_executable(indie WIN32  ${SOURCE_FILES})
	TARGET_LINK_LIBRARIES(indie "../winInc/legacy_stdio_definitions" "../winInc/Irrlicht" "../winInc/sfml-audio" "../winInc/sfml-system" "../winInc/freetype" "../winInc/libboost_serialization-vc140-mt-1_63" "../winInc/libboost_serialization-vc140-mt-gd-1_63")
else()
	add_executable(indie ${SOURCE_FILES})
    TARGET_LINK_LIBRARIES(indie "Irrlicht" "sfml-audio" "sfml-system" "freetype" "boost_serialization" "pthread" "openal" "png" "z")
endif()
