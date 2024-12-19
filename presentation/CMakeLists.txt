cmake_minimum_required(VERSION 3.16)

project(
  presentation
  VERSION 1.0
  LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(HEADERS
    include/App.hpp
    # Utilities
    include/Utils/TextBuilder.hpp
    include/Utils/FontFactory.hpp
    # Interfaces
    include/Interfaces/Widget.hpp
    # include/Interfaces/View.hpp
    # Components
    include/Components/BackgroundManager.hpp
    include/Components/SFXPlayer.hpp
    include/Components/MusicPlayer.hpp
    include/Components/IButton.hpp
    include/Components/StandardButton.hpp
    include/Components/TextButton.hpp
    include/Components/IconButton.hpp
    include/Components/LevelButton.hpp
    include/Components/PageManager.hpp
    include/Components/PageFactory.hpp
    include/Components/Page.hpp
    include/Components/Title.hpp
    # Widget
    include/Widgets/MuteButton.hpp
    # Pages
    include/Pages/MainMenu.hpp
    include/Pages/LevelsPage.hpp)
set(SOURCES
    src/App.cpp
    # Utilities
    src/Utils/TextBuilder.cpp
    src/Utils/FontFactory.cpp
    # Components
    src/Components/BackgroundManager.cpp
    src/Components/MusicPlayer.cpp
    src/Components/SFXPlayer.cpp
    src/Components/IButton.cpp
    src/Components/StandardButton.cpp
    src/Components/TextButton.cpp
    src/Components/IconButton.cpp
    src/Components/LevelButton.cpp
    src/Components/PageFactory.cpp
    src/Components/PageManager.cpp
    src/Components/Page.cpp
    src/Components/Title.cpp
    # Interfaces
    # src/Interfaces/View.cpp
    # Widget
    src/Widgets/MuteButton.cpp
    # Pages
    src/Pages/MainMenu.cpp
    src/Pages/LevelsPage.cpp)

add_library(presentation ${HEADERS} ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

target_compile_features(presentation PRIVATE cxx_std_17)

# Linking libraries
target_link_libraries(presentation PRIVATE sfml-graphics sfml-audio business)

# Include directories
target_include_directories(
  presentation
  PUBLIC ${PROJECT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/business/include
         ${CMAKE_SOURCE_DIR}/dependencies/SFML/include)
