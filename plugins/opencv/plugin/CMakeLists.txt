cmake_minimum_required(VERSION 3.14)

project(opencv_plugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# - - - Add OpenCV lib
if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set("OpenCV_DIR" "E:/libs/opencv-4.5.2/debug/x64/vc15/lib")
        # Note: be sure "E:/libs/opencv-4.5.2/debug/x64/vc15/bin" is in PATH
    else()
        set("OpenCV_DIR" "E:/libs/opencv-4.5.2/release/x64/vc15/staticlib") # Win64
        #set("OpenCV_DIR" "E:/libs/opencv-4.5.3/release/x86/vc16/staticlib") # Win32
    endif()
endif()

if(UNIX)
    set("OpenCV_DIR" "/home/user/opencv-4.5.3/build/lib")
endif()

find_package(OpenCV REQUIRED)
set(CMAKE_DEBUG_POSTFIX d)
# - - -

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# - - - Use headers from main project
include_directories(../../../app/src/plugins)

add_library(opencv_plugin SHARED
#add_library(opencv_plugin STATIC # For static plugin
    opencvplugin.cpp
    opencvplugin.h
    resource_opencv.qrc
    # - - - Use headers from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/visionplugin.h
    ../../../app/src/plugins/visionplugin.cpp
    )

# - - - link OpenCV libs
target_link_libraries(opencv_plugin PRIVATE Qt${QT_VERSION_MAJOR}::Core ${OpenCV_LIBS})
target_compile_definitions(opencv_plugin PRIVATE OPENCV_PLUGIN_LIBRARY)
set_target_properties(opencv_plugin PROPERTIES PREFIX "")

# - - - For static plugin
#target_compile_definitions(opencv_plugin PUBLIC QT_STATICPLUGIN)
#set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# - - -

# - - - Copy dll to plugins folder
if(APP_BUILD_PLUGINS)
    if(MSVC)
        set(file_name "opencv_plugin.dll")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(file_name "opencv_plugind.dll")
        endif()
    endif()

    if(UNIX)
        set(file_name "opencv_plugin.so")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(file_name "opencv_plugind.so")
        endif()
    endif()

    add_custom_command(TARGET opencv_plugin
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/${file_name}"
        "${CMAKE_BINARY_DIR}/app/plugins/${file_name}")
endif()
