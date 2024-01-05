cmake_minimum_required(VERSION 3.16)

project(
  app-tests
  LANGUAGES CXX)

add_subdirectory(debug-app)
add_subdirectory(debug-database)
add_subdirectory(debug-qml)
add_subdirectory(test-commands)
add_subdirectory(test-database)
