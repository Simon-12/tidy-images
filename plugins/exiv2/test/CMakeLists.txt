cmake_minimum_required(VERSION 3.16)

project(
  exiv2-test
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing(true)

find_package(
  Qt6 6.2
  COMPONENTS Core Test
  REQUIRED)

if(APP_STATIC_PLUGINS)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  find_package(
    exiv2
    REQUIRED
    CONFIG
    NAMES
    exiv2)
  add_definitions(-DAPP_STATIC_PLUGINS)
endif()

add_executable(
  exiv2-test
  test.h
  test.cpp
  # Use files from main project
  ../../../app/src/plugins/baseplugin.h
  ../../../app/src/plugins/exivplugin.h
  ../../../app/src/plugins/exivplugin.cpp)

# Use files from main project
include_directories(../../../app/src/plugins)

target_link_libraries(
  exiv2-test Qt6::Core Qt6::Test)

if(APP_STATIC_PLUGINS)
  target_link_libraries(
    exiv2-test
    Qt6::Core
    Qt6::Test
    exiv2_plugin
    exiv2lib
    exiv2-xmp
    libexpat
    zlibstatic)
endif()

# Copy samples
file(GLOB samples "../../../samples/*.jpg")
file(COPY ${samples} DESTINATION "../samples")
