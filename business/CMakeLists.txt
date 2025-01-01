cmake_minimum_required(VERSION 3.16)

project(
  business
  VERSION 1.0
  LANGUAGES CXX)

set(HEADERS
    include/Game.hpp
    include/GameSettings.hpp
    include/Level.hpp
    include/LevelReader.hpp
    include/WaveManager.hpp
    # Utils
    include/Utils/Positionable.hpp
    include/Utils/Moveable.hpp
    include/Utils/Vector.hpp
    include/Utils/Collidable.hpp
    # Tower
    include/Tower/BaseTower.hpp
    include/Tower/TowerManager.hpp
    # Towers
    include/Tower/Towers/ArcheryTower.hpp
    include/Tower/Towers/ElectroTower.hpp
    include/Tower/Towers/SlingshotTower.hpp
    include/Tower/Towers/CatapultTower.hpp
    include/Tower/Towers/OrbTower.hpp
    include/Tower/Towers/CrossbowTower.hpp
    # Enemy
    include/Enemy/BaseEnemy.hpp
    include/Enemy/EnemyFactory.hpp
    include/Enemy/EnemyManager.hpp
    # Enemies
    include/Enemy/Enemies/LeafBug.hpp
    include/Enemy/Enemies/FireBug.hpp
    include/Enemy/Enemies/FireWasp.hpp
    include/Enemy/Enemies/FlyingLocust.hpp
    include/Enemy/Enemies/MagmaCrab.hpp
    include/Enemy/Enemies/ClampBeetle.hpp
    include/Enemy/Enemies/VoidButterfly.hpp
    # Map
    include/Map/Map.hpp
    include/Map/BaseTile.hpp
    include/Map/BuildableTile.hpp
    include/Map/NonBuildableTile.hpp
    include/Map/EnemyPathTile.hpp
    # Attack
    include/Attack/BaseAttack.hpp
    include/Attack/AttackManager.hpp
    # Attacks
    include/Attack/Attacks/ArcheryAttack.hpp
    include/Attack/Attacks/ElectroAttack.hpp
    include/Attack/Attacks/SlingshotAttack.hpp
    include/Attack/Attacks/CatapultAttack.hpp
    include/Attack/Attacks/OrbAttack.hpp
    include/Attack/Attacks/CrossbowAttack.hpp
    )

set(SOURCES # Sources
    src/Game.cpp
    src/GameSettings.cpp
    src/Level.cpp
    src/LevelReader.cpp
    src/WaveManager.cpp
    # Utils
    src/Utils/Positionable.cpp
    src/Utils/Moveable.cpp
    src/Utils/Collidable.cpp
    # Tower
    src/Tower/BaseTower.cpp
    src/Tower/TowerManager.cpp
    # Towers
    src/Tower/Towers/ArcheryTower.cpp
    src/Tower/Towers/CatapultTower.cpp
    src/Tower/Towers/ElectroTower.cpp
    src/Tower/Towers/SlingshotTower.cpp
    src/Tower/Towers/OrbTower.cpp
    src/Tower/Towers/CrossbowTower.cpp

    # Enemy
    src/Enemy/BaseEnemy.cpp
    src/Enemy/EnemyFactory.cpp
    src/Enemy/EnemyManager.cpp
    # Enemies
    src/Enemy/Enemies/LeafBug.cpp
    src/Enemy/Enemies/MagmaCrab.cpp
    src/Enemy/Enemies/ClampBeetle.cpp
    src/Enemy/Enemies/FireBug.cpp
    src/Enemy/Enemies/FireWasp.cpp
    src/Enemy/Enemies/FlyingLocust.cpp
    src/Enemy/Enemies/VoidButterfly.cpp
    # Map
    src/Map/Map.cpp
    src/Map/BaseTile.cpp
    src/Map/BuildableTile.cpp
    src/Map/NonBuildableTile.cpp
    src/Map/EnemyPathTile.cpp
    # Attack
    src/Attack/BaseAttack.cpp
    src/Attack/AttackManager.cpp
    # Attacks
    src/Attack/Attacks/ArcheryAttack.cpp
    src/Attack/Attacks/ElectroAttack.cpp
    src/Attack/Attacks/SlingshotAttack.cpp
    src/Attack/Attacks/CatapultAttack.cpp
    src/Attack/Attacks/OrbAttack.cpp
    src/Attack/Attacks/CrossbowAttack.cpp

    )

add_library(business ${HEADERS} ${SOURCES})
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

# Include directories
target_include_directories(business PUBLIC ${PROJECT_SOURCE_DIR}/include)
