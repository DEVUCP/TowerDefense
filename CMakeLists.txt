cmake_minimum_required(VERSION 3.16)

project(main VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_subdirectory(./presentation)
add_subdirectory(./business)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE business)
target_link_libraries(main PRIVATE presentation)

