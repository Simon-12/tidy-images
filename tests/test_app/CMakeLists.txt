cmake_minimum_required(VERSION 3.5)

project(test_app LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

find_package(QT NAMES Qt5 Qt6 COMPONENTS Core Quick Widgets Concurrent Sql Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets Concurrent Sql Test REQUIRED)

set(PROJECT_SOURCES
    ../../app/src/options.h
    ../../app/src/settings.h
    ../../app/src/support.h
    ../../app/src/qmlcontroller.h
    ../../app/src/qmlcontroller.cpp
    ../../app/src/logger.h
    ../../app/src/logger.cpp
    ../../app/src/loaderclass.h
    ../../app/src/loaderclass.cpp
    ../../app/src/applicationinfo.h
    ../../app/src/applicationinfo.cpp
    ../../app/src/iconitem.h
    ../../app/src/iconmodel.h
    ../../app/src/iconmodel.cpp

    ../../app/src/plugins/baseplugin.h
    ../../app/src/plugins/exivplugin.h
    ../../app/src/plugins/exivplugin.cpp
    ../../app/src/plugins/visionplugin.h
    ../../app/src/plugins/visionplugin.cpp
    ../../app/src/plugins/pluginloader.h
    ../../app/src/plugins/pluginloader.cpp
    ../../app/src/plugins/pluginitem.h
    ../../app/src/plugins/pluginmodel.h
    ../../app/src/plugins/pluginmodel.cpp

    ../../app/src/filehandler/basehandler.h
    ../../app/src/filehandler/basehandler.cpp
    ../../app/src/filehandler/confighandler.h
    ../../app/src/filehandler/confighandler.cpp
    ../../app/src/filehandler/folderfiltermodel.h
    ../../app/src/filehandler/folderfiltermodel.cpp
    ../../app/src/filehandler/folderhandler.h
    ../../app/src/filehandler/folderhandler.cpp
    ../../app/src/filehandler/folderitem.h
    ../../app/src/filehandler/foldermodel.h
    ../../app/src/filehandler/foldermodel.cpp

    ../../app/src/listhandler/listhandler.h
    ../../app/src/listhandler/listhandler.cpp
    ../../app/src/listhandler/listsort.h
    ../../app/src/listhandler/listsort.cpp
    ../../app/src/listhandler/imageprovider.h
    ../../app/src/listhandler/imageprovider.cpp

    ../../app/src/listhandler/basefile/basefile.h
    ../../app/src/listhandler/basefile/basefile.cpp
    ../../app/src/listhandler/basefile/imagefile.h
    ../../app/src/listhandler/basefile/imagefile.cpp
    ../../app/src/listhandler/basefile/videofile.h
    ../../app/src/listhandler/basefile/videofile.cpp

    ../../app/src/listhandler/command/commandlist.h
    ../../app/src/listhandler/command/commandlist.cpp
    ../../app/src/listhandler/command/commanddata.h
    ../../app/src/listhandler/command/basecommand.h
    ../../app/src/listhandler/command/basecommand.cpp
    ../../app/src/listhandler/command/commanditem.h
    ../../app/src/listhandler/command/commandmodel.h
    ../../app/src/listhandler/command/commandmodel.cpp
    ../../app/src/listhandler/command/copycommand.h
    ../../app/src/listhandler/command/copycommand.cpp
    ../../app/src/listhandler/command/favoritecommand.h
    ../../app/src/listhandler/command/favoritecommand.cpp
    ../../app/src/listhandler/command/movecommand.h
    ../../app/src/listhandler/command/movecommand.cpp

    ../../app/src/listhandler/models/fileitem.h
    ../../app/src/listhandler/models/filemodel.h
    ../../app/src/listhandler/models/filemodel.cpp
    ../../app/src/listhandler/models/listmodels.h
    ../../app/src/listhandler/models/imagemodel.h
    ../../app/src/listhandler/models/imagemodel.cpp
    ../../app/src/listhandler/models/labelmodel.h
    ../../app/src/listhandler/models/labelmodel.cpp

    ../../app/src/listhandler/compare/comparelist.h
    ../../app/src/listhandler/compare/comparelist.cpp
    ../../app/src/listhandler/compare/tablemodel.h
    ../../app/src/listhandler/compare/tablemodel.cpp

    ../../app/src/listhandler/database/database.h
    ../../app/src/listhandler/database/database.cpp
    ../../app/src/listhandler/database/sqlhandler.h
    ../../app/src/listhandler/database/sqlhandler.cpp
    ../../app/src/listhandler/database/headeritem.h
    ../../app/src/listhandler/database/headermodel.h
    ../../app/src/listhandler/database/headermodel.cpp
    )

include_directories(../../app/src)

add_executable(test_app
    ${PROJECT_SOURCES}
    testapp.h
    testapp.cpp)

add_test(NAME test_app COMMAND test_app)

target_link_libraries(test_app
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Test)

# Copy example images
file(GLOB ImageFiles "../../samples/*.jpg")
file(COPY ${ImageFiles} DESTINATION "samples")
