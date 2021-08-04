cmake_minimum_required(VERSION 3.14)

project(exiv2_plugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# - - - Add Exiv2 lib
if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set("exiv2_DIR" "E:/libs/exiv2-0.27.3/debug/lib/cmake/exiv2")
        # Note: be sure "E:/libs/exiv2-0.27.3/debug/bin" is in PATH
    else()
        set("exiv2_DIR" "E:/libs/exiv2-0.27.3/release/lib/cmake/exiv2") # Win64
        #set("exiv2_DIR" "E:/libs/exiv2-0.27.4/release/lib/cmake/exiv2") # Win32
    endif()
endif()

if(UNIX)
    set("exiv2_DIR" "/home/user/exiv2-0.27.4/build/lib/cmake/exiv2")
endif()

find_package(exiv2 REQUIRED CONFIG NAMES exiv2)
set(CMAKE_DEBUG_POSTFIX d)
# - - -

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# - - - Use headers from main project
include_directories(../../../app/src/plugins)

add_library(exiv2_plugin SHARED
#add_library(exiv2_plugin STATIC # For static plugin
    exiv2plugin.cpp
    exiv2plugin.h
    resource_exiv2.qrc
    # - - - Use headers from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/exivplugin.h
    ../../../app/src/plugins/exivplugin.cpp
    )

# - - - link exiv2lib
target_link_libraries(exiv2_plugin PRIVATE Qt${QT_VERSION_MAJOR}::Core exiv2lib)
target_compile_definitions(exiv2_plugin PRIVATE EXIV2_PLUGIN_LIBRARY)
set_target_properties(exiv2_plugin PROPERTIES PREFIX "")

# - - - For static plugin
#target_compile_definitions(exiv2_plugin PUBLIC QT_STATICPLUGIN)
#set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# - - -

# - - - Copy dll to plugins folder
if(APP_BUILD_PLUGINS)
    if(MSVC)
        set(file_name "exiv2_plugin.dll")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(file_name "exiv2_plugind.dll")
        endif()
    endif()

    if(UNIX)
        set(file_name "exiv2_plugin.so")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(file_name "exiv2_plugind.so")
        endif()
    endif()

    add_custom_command(TARGET exiv2_plugin
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/${file_name}"
        "${CMAKE_BINARY_DIR}/app/plugins/${file_name}")
endif()
