cmake_minimum_required(VERSION 3.16)

project(
  presentation
  VERSION 1.0
  LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(HEADERS include/App.hpp)
set(SOURCES src/App.cpp)

add_library(presentation ${HEADERS} ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Linking libraries
target_link_libraries(presentation PRIVATE sfml-graphics sfml-audio sfml-system)
include_directories(${CMAKE_SOURCE_DIR}/business/include)

# Include directories
target_include_directories(
  presentation PUBLIC ${PROJECT_SOURCE_DIR}/include
                      ${CMAKE_SOURCE_DIR}/business/include)
