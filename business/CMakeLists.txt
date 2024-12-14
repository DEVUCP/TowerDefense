cmake_minimum_required(VERSION 3.16)

project(
  business
  VERSION 1.0
  LANGUAGES CXX)

set(HEADERS include/Game.hpp)
set(SOURCES src/Game.cpp)

add_library(business ${HEADERS} ${SOURCES})

# Include directories
target_include_directories(business PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(business PUBLIC ${PROJECT_SOURCE_DIR}/public)
