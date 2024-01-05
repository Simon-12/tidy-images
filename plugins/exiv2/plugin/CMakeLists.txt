cmake_minimum_required(VERSION 3.16)

project(
  exiv2-plugin
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Exiv2 lib
# ~~~
# set(exiv2_DIR "")
# set(EXPAT_LIBRARY "")
# set(EXPAT_INCLUDE_DIR "")
# set(ZLIB_LIBRARY "")
# set(ZLIB_INCLUDE_DIR "")
# set(Iconv_LIBRARY "")
# set(Iconv_INCLUDE_DIR "")
# ~~~
find_package(exiv2 REQUIRED)
find_package(EXPAT)
find_package(ZLIB)
find_package(Iconv)

find_package(
  Qt6 6.2
  COMPONENTS Core
  REQUIRED)

if(APP_STATIC_PLUGINS)
  add_library(
    exiv2-plugin STATIC
    exiv2plugin.cpp
    exiv2plugin.h
    resource_exiv2.qrc
    # Use files from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/exivplugin.h
    ../../../app/src/plugins/exivplugin.cpp)
else()
  add_library(
    exiv2-plugin SHARED
    exiv2plugin.cpp
    exiv2plugin.h
    resource_exiv2.qrc
    # Use files from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/exivplugin.h
    ../../../app/src/plugins/exivplugin.cpp)
endif()

# Use files from main project
include_directories(../../../app/src/plugins)

# Link Exiv2 lib
target_link_libraries(
  exiv2-plugin
  PRIVATE Qt6::Core exiv2lib)
target_compile_definitions(exiv2-plugin PRIVATE EXIV2_PLUGIN_LIBRARY)
set_target_properties(exiv2-plugin PROPERTIES PREFIX "")
set(CMAKE_DEBUG_POSTFIX d)

if(APP_STATIC_PLUGINS)
  target_compile_definitions(exiv2-plugin PUBLIC QT_STATICPLUGIN)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
endif()

# Copy dll to plugins folder
if(APP_BUILD_PLUGINS)
  if(MSVC OR MINGW)
    set(file_name "exiv2-plugin.dll")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(file_name "exiv2-plugind.dll")
    endif()
    if(APP_STATIC_PLUGINS)
      set(file_name "exiv2-plugin.lib")
    endif()
  endif()

  if(UNIX)
    set(file_name "exiv2-plugin.so")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(file_name "exiv2-plugind.so")
    endif()
  endif()

  add_custom_command(
    TARGET exiv2-plugin
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${file_name}"
            "${CMAKE_BINARY_DIR}/app/plugins/${file_name}")
endif()
