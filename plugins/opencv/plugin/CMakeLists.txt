cmake_minimum_required(VERSION 3.16)

project(
  opencv-plugin
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add OpenCV lib
# ~~~
# set(OpenCV_DIR "")
# ~~~
find_package(OpenCV REQUIRED)

find_package(
  Qt6 6.2
  COMPONENTS Core
  REQUIRED)

if(APP_STATIC_PLUGINS)
  add_library(
    opencv-plugin STATIC
    opencvplugin.cpp
    opencvplugin.h
    resource_opencv.qrc
    # Use files from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/visionplugin.h
    ../../../app/src/plugins/visionplugin.cpp)
else()
  add_library(
    opencv-plugin SHARED
    opencvplugin.cpp
    opencvplugin.h
    resource_opencv.qrc
    # Use files from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/visionplugin.h
    ../../../app/src/plugins/visionplugin.cpp)
endif()

# Use files from main project
include_directories(../../../app/src/plugins)

# Link OpenCV libs
target_link_libraries(
  opencv-plugin
  PRIVATE Qt6::Core ${OpenCV_LIBS})
target_compile_definitions(opencv-plugin PRIVATE OPENCV_PLUGIN_LIBRARY)
set_target_properties(opencv-plugin PROPERTIES PREFIX "")
set(CMAKE_DEBUG_POSTFIX d)

if(APP_STATIC_PLUGINS)
  target_compile_definitions(opencv-plugin PUBLIC QT_STATICPLUGIN)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
endif()

# Copy dll to plugins folder
if(APP_BUILD_PLUGINS)
  if(MSVC OR MINGW)
    set(file_name "opencv-plugin.dll")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(file_name "opencv-plugind.dll")
    endif()
    if(APP_STATIC_PLUGINS)
      set(file_name "opencv-plugin.lib")
    endif()
  endif()

  if(UNIX)
    set(file_name "opencv-plugin.so")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(file_name "opencv-plugind.so")
    endif()
  endif()

  add_custom_command(
    TARGET opencv-plugin
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${file_name}"
            "${CMAKE_BINARY_DIR}/app/plugins/${file_name}")
endif()
