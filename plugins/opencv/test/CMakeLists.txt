cmake_minimum_required(VERSION 3.14)

project(opencv_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# - - - For static plugin
#set(CMAKE_CXX_FLAGS_RELEASE "/MT")
#set("OpenCV_DIR" "E:/libs/opencv-4.5.3/release/x86/vc16/staticlib") # Win32
#find_package(OpenCV REQUIRED)
# - - -

# - - - Use headers from main project
include_directories(../../../app/src/plugins)

add_executable(opencv_test
    main.cpp
    # - - - Use headers from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/visionplugin.h
    ../../../app/src/plugins/visionplugin.cpp
    )

target_link_libraries(opencv_test Qt${QT_VERSION_MAJOR}::Core)

# - - - For static plugin
#target_link_libraries(opencv_test
#    Qt${QT_VERSION_MAJOR}::Core
#    ${CMAKE_BINARY_DIR}/plugin/opencv_plugin.lib
#    ${OpenCV_LIBS})
