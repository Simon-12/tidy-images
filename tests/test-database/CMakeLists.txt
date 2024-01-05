cmake_minimum_required(VERSION 3.16)

project(
  test-database
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
  COMPONENTS Core
             Quick
             Widgets
             Concurrent
             Sql
             Test
  REQUIRED)

qt_add_executable(
  test-database
  test.h
  test.cpp
  # Use files from main project
  ../../app/src/options.h
  ../../app/src/settings.h
  ../../app/src/support.h
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
  ../../app/src/listhandler/command/movelistcommand.h
  ../../app/src/listhandler/command/movelistcommand.cpp
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
  ../../app/src/listhandler/database/headermodel.cpp)

# Use files from main project
include_directories(../../app/src)

add_test(NAME test-database COMMAND test-database)

target_link_libraries(
  test-database
  PRIVATE Qt6::Core
          Qt6::Quick
          Qt6::Widgets
          Qt6::Concurrent
          Qt6::Sql
          Qt6::Test)

# Copy example images
file(GLOB ImageFiles "../../samples/*.jpg")
file(COPY ${ImageFiles} DESTINATION "samples")
