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
    include/Utils/Drawable.hpp
    include/Utils/Moveable.hpp
    include/Utils/Vector.hpp
    include/Utils/Collidable.hpp
    # Tower
    include/Tower/BaseTower.hpp
    include/Tower/TowerManager.hpp
    # Enemy
    include/Enemy/BaseEnemy.hpp
    include/Enemy/EnemyFactory.hpp
    include/Enemy/EnemyManager.hpp
    # Map
    include/Map/Map.hpp
    include/Map/BaseTile.hpp
    include/Map/BuildableTile.hpp
    include/Map/NonBuildableTile.hpp
    include/Map/EnemyPathTile.hpp
    # Attack
    include/Attack/BaseAttack.hpp
    include/Attack/AttackManager.hpp)

set(SOURCES # Sources
    src/Game.cpp
    src/GameSettings.cpp
    src/Level.cpp
    src/LevelReader.cpp
    # Utils
    src/Utils/Moveable.cpp
    src/Utils/Drawable.cpp
    src/Utils/Collidable.cpp
    # Enemy
    src/Enemy/BaseEnemy.cpp
    src/Enemy/EnemyManager.cpp
    # Map
    src/Map/Map.cpp)

add_library(business ${HEADERS} ${SOURCES})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../)

# Include directories
target_include_directories(business PUBLIC ${PROJECT_SOURCE_DIR}/include)
