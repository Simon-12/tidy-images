cmake_minimum_required(VERSION 3.16)

project(
  opencv-project
  LANGUAGES CXX)

add_subdirectory(plugin)
add_subdirectory(debug)
add_subdirectory(test)
