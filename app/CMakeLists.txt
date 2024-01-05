cmake_minimum_required(VERSION 3.16)

# Project name
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt6 6.2
  COMPONENTS Core
             Quick
             QmlImportScanner
             Widgets
             Concurrent
             Sql
             Multimedia
  REQUIRED)

if(APP_STATIC_PLUGINS)
  find_package(OpenCV REQUIRED)
  find_package(
    exiv2
    REQUIRED
    CONFIG
    NAMES
    exiv2)
  link_directories("E:/libs/exiv2-0.27.4/release/lib")
  add_definitions(-DAPP_STATIC_PLUGINS)
endif()

# Add the resource file
set(RESOURCE_FILE
    data/data.qrc
    icons/icons.qrc
    qml/qml.qrc)
qt_add_resources(RESOURCE_FILES ${RESOURCE_FILE})

qt_add_executable(
  ${CMAKE_PROJECT_NAME}
  src/main.cpp
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
  src/listhandler/command/movelistcommand.h
  src/listhandler/command/movelistcommand.cpp
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
  ${RESOURCE_FILES})

# Avoids long headers (sorry)
include_directories(src)

qt_add_qml_module(
  ${CMAKE_PROJECT_NAME}
  URI qml.components
  VERSION 1.0
  QML_FILES
  qml/Main.qml
  qml/components/SliderCustom.qml
  qml/components/Triangle.qml
  qml/components/BackgroundDefault.qml
  qml/components/ButtonClose.qml
  qml/components/ButtonDefault.qml
  qml/components/ButtonDraggable.qml
  qml/components/ButtonIcon.qml
  qml/components/ButtonIconColor.qml
  qml/components/ComboBoxDefault.qml
  qml/components/GroupBoxDefault.qml
  qml/components/ImageDefault.qml
  qml/components/MenuCheckBox.qml
  qml/components/MenuDefault.qml
  qml/components/RoundButtonDefault.qml
  qml/core/VideoItem.qml
  qml/core/ColumnButtons.qml
  qml/core/EmptyMain.qml
  qml/core/FileItem.qml
  qml/core/FocusHandler.qml
  qml/core/GalleryMain.qml
  qml/core/ImageItem.qml
  qml/core/ListButtons.qml
  qml/core/MenuBarMain.qml
  qml/core/StatusBarMain.qml
  qml/core/SupportFunctions.js
  qml/core/SwipeFileView.qml
  qml/core/SwipeImageView.qml
  qml/core/VideoButtons.qml
  qml/core/VideoFrameItem.qml
  qml/dialogs/PathBox.qml
  qml/dialogs/PopupDefault.qml
  qml/dialogs/DialogFolder.qml
  qml/dialogs/DialogHistory.qml
  qml/dialogs/DialogInfo.qml
  qml/dialogs/DialogLoader.qml
  qml/dialogs/DialogPlugin.qml
  qml/dialogs/DialogSettings.qml
  qml/dialogs/FolderBox.qml
  qml/dialogs/HistoryBox.qml
  qml/dialogs/LabelLink.qml
  qml/labelbar/LabelBarMain.qml
  qml/labelbar/LabelEditField.qml
  qml/labelbar/LabelField.qml
  qml/database/HeaderFilter.qml
  qml/database/TableDatabase.qml
  qml/database/DatabaseMain.qml
  qml/database/HeaderButton.qml
  qml/compare/ParameterCompare.qml
  qml/compare/TableCompare.qml
  qml/compare/CompareMain.qml
  qml/compare/DialogCompare.qml
  qml/compare/ImageButtons.qml)

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PRIVATE Qt6::Core
          Qt6::Quick
          Qt6::Widgets
          Qt6::Concurrent
          Qt6::Sql
          Qt6::Multimedia)

if(APP_STATIC_BUILD)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  qt5_import_qml_plugins(${CMAKE_PROJECT_NAME})

  if(APP_STATIC_PLUGINS)
    target_link_libraries(
      ${CMAKE_PROJECT_NAME}
      PRIVATE Qt6::Core
              Qt6::Quick
              Qt6::Widgets
              Qt6::Concurrent
              Qt6::Sql
              Qt6::Multimedia
              opencv_plugin
              ${OpenCV_LIBS}
              exiv2_plugin
              exiv2lib
              exiv2-xmp
              libexpat
              zlibstatic)
  endif()
endif()

install(
  TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
