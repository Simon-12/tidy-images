cmake_minimum_required(VERSION 3.14)

project(exiv2_test LANGUAGES CXX)

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
#set("exiv2_DIR" "E:/libs/exiv2-0.27.4/release/lib/cmake/exiv2") # Win32
#find_package(exiv2 REQUIRED CONFIG NAMES exiv2)
# - - -

# - - - Use headers from main project
include_directories(../../../app/src/plugins)

add_executable(exiv2_test
    main.cpp
    # - - - Use headers from main project
    ../../../app/src/plugins/baseplugin.h
    ../../../app/src/plugins/exivplugin.h
    ../../../app/src/plugins/exivplugin.cpp
    )

target_link_libraries(exiv2_test Qt${QT_VERSION_MAJOR}::Core)

# - - - For static plugin
#target_link_libraries(exiv2_test
#    Qt${QT_VERSION_MAJOR}::Core
#    ${CMAKE_BINARY_DIR}/plugin/exiv2_plugin.lib
#    exiv2lib
#    "E:/libs/exiv2-0.27.4/release/lib/exiv2-xmp.lib"
#    "E:/libs/exiv2-0.27.4/release/lib/libexpat.lib"
#    "E:/libs/exiv2-0.27.4/release/lib/zlibstatic.lib")
