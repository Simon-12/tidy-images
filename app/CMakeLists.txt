cmake_minimum_required(VERSION 3.14)

get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

# - - - For static plugins
#set("OpenCV_DIR" "E:/libs/opencv-4.5.3/release/x86/vc16/staticlib") # Win32
#set("exiv2_DIR" "E:/libs/exiv2-0.27.4/release/lib/cmake/exiv2") # Win32
#find_package(OpenCV REQUIRED)
#find_package(exiv2 REQUIRED CONFIG NAMES exiv2)
# - - -

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick QmlImportScanner Widgets Concurrent Sql Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QmlImportScanner Widgets Concurrent Sql Multimedia REQUIRED)

set(PROJECT_SOURCES

    src/main.cpp
    data/data.qrc
    icons/icons.qrc
    qml/qml.qrc

    src/options.h
    src/settings.h
    src/support.h
    src/qmlcontroller.h
    src/qmlcontroller.cpp
    src/logger.h
    src/logger.cpp
    src/loaderclass.h
    src/loaderclass.cpp
    src/applicationinfo.h
    src/applicationinfo.cpp
    src/iconitem.h
    src/iconmodel.h
    src/iconmodel.cpp

    src/plugins/baseplugin.h
    src/plugins/exivplugin.h
    src/plugins/exivplugin.cpp
    src/plugins/visionplugin.h
    src/plugins/visionplugin.cpp
    src/plugins/pluginloader.h
    src/plugins/pluginloader.cpp
    src/plugins/pluginitem.h
    src/plugins/pluginmodel.h
    src/plugins/pluginmodel.cpp

    src/filehandler/basehandler.h
    src/filehandler/basehandler.cpp
    src/filehandler/confighandler.h
    src/filehandler/confighandler.cpp
    src/filehandler/folderfiltermodel.h
    src/filehandler/folderfiltermodel.cpp
    src/filehandler/folderhandler.h
    src/filehandler/folderhandler.cpp
    src/filehandler/folderitem.h
    src/filehandler/foldermodel.h
    src/filehandler/foldermodel.cpp

    src/listhandler/listhandler.h
    src/listhandler/listhandler.cpp
    src/listhandler/listsort.h
    src/listhandler/listsort.cpp
    src/listhandler/imageprovider.h
    src/listhandler/imageprovider.cpp

    src/listhandler/basefile/basefile.h
    src/listhandler/basefile/basefile.cpp
    src/listhandler/basefile/imagefile.h
    src/listhandler/basefile/imagefile.cpp
    src/listhandler/basefile/videofile.h
    src/listhandler/basefile/videofile.cpp

    src/listhandler/command/commandlist.h
    src/listhandler/command/commandlist.cpp
    src/listhandler/command/commanddata.h
    src/listhandler/command/basecommand.h
    src/listhandler/command/basecommand.cpp
    src/listhandler/command/commanditem.h
    src/listhandler/command/commandmodel.h
    src/listhandler/command/commandmodel.cpp
    src/listhandler/command/copycommand.h
    src/listhandler/command/copycommand.cpp
    src/listhandler/command/favoritecommand.h
    src/listhandler/command/favoritecommand.cpp
    src/listhandler/command/movecommand.h
    src/listhandler/command/movecommand.cpp

    src/listhandler/models/fileitem.h
    src/listhandler/models/filemodel.h
    src/listhandler/models/filemodel.cpp
    src/listhandler/models/listmodels.h
    src/listhandler/models/imagemodel.h
    src/listhandler/models/imagemodel.cpp
    src/listhandler/models/labelmodel.h
    src/listhandler/models/labelmodel.cpp

    src/listhandler/compare/comparelist.h
    src/listhandler/compare/comparelist.cpp
    src/listhandler/compare/tablemodel.h
    src/listhandler/compare/tablemodel.cpp

    src/listhandler/database/database.h
    src/listhandler/database/database.cpp
    src/listhandler/database/sqlhandler.h
    src/listhandler/database/sqlhandler.cpp
    src/listhandler/database/headeritem.h
    src/listhandler/database/headermodel.h
    src/listhandler/database/headermodel.cpp
    )

include_directories(src) # Avoids long headers (sorry)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${CMAKE_PROJECT_NAME}
        ${PROJECT_SOURCES}
        )
else()
    if(ANDROID)
        add_library(${CMAKE_PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
            )
    else()
        add_executable(${CMAKE_PROJECT_NAME}
            ${PROJECT_SOURCES}
            )
    endif()
endif()

target_compile_definitions(${CMAKE_PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Multimedia)

# - - - For static build
#set(CMAKE_CXX_FLAGS_RELEASE "/MT")
#qt5_import_qml_plugins(${CMAKE_PROJECT_NAME})
#target_link_libraries(${CMAKE_PROJECT_NAME}
#    PRIVATE Qt${QT_VERSION_MAJOR}::Core
#    Qt${QT_VERSION_MAJOR}::Quick
#    Qt${QT_VERSION_MAJOR}::Widgets
#    Qt${QT_VERSION_MAJOR}::Concurrent
#    Qt${QT_VERSION_MAJOR}::Sql
#    Qt${QT_VERSION_MAJOR}::Multimedia
#    ${CMAKE_BINARY_DIR}/plugins/opencv_plugin.lib
#    ${OpenCV_LIBS}
#    ${CMAKE_BINARY_DIR}/plugins/exiv2_plugin.lib
#    exiv2lib
#    "E:/libs/exiv2-0.27.4/release/lib/exiv2-xmp.lib"
#    "E:/libs/exiv2-0.27.4/release/lib/libexpat.lib"
#    "E:/libs/exiv2-0.27.4/release/lib/zlibstatic.lib")
