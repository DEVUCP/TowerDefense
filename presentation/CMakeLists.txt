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
    # Interfaces
    include/Interfaces/Widget.hpp
    # Components
    include/Components/BackgroundManager.hpp
    include/Components/Button.hpp
    include/Components/PageManager.hpp
    include/Components/PageFactory.hpp
    include/Components/Page.hpp
    # Pages
    include/Pages/MainMenu.hpp
    # MainMenu Widgets
    include/Widgets/MainMenu/Title.hpp)
set(SOURCES
    src/App.cpp
    # Utilities
    src/Utils/TextBuilder.cpp
    # Components
    src/Components/BackgroundManager.cpp
    src/Components/Button.cpp
    src/Components/PageFactory.cpp
    src/Components/PageManager.cpp
    src/Components/Page.cpp
    # Pages
    src/Pages/MainMenu.cpp
    # MainMenu Widgets
    src/Widgets/MainMenu/Title.cpp)

add_library(presentation ${HEADERS} ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

target_compile_features(presentation PRIVATE cxx_std_17)

# Linking libraries
target_link_libraries(presentation PRIVATE sfml-graphics)
include_directories(${CMAKE_SOURCE_DIR}/business/include)

# Include directories
target_include_directories(
  presentation
  PUBLIC ${PROJECT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/business/include
         ${CMAKE_SOURCE_DIR}/dependencies/SFML/include)
