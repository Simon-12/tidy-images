cmake_minimum_required(VERSION 3.16)

project(
  debug-qml
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt6 6.4
  COMPONENTS Core Quick
  REQUIRED)

qt_standard_project_setup()

# Add the resource file
set(RESOURCE_FILE ../../app/icons/icons.qrc ../../app/qml/qml.qrc)
qt_add_resources(RESOURCE_FILES ${RESOURCE_FILE})

qt_add_executable(
  debug-qml main.cpp
  # Use files from main project
  ../../app/src/options.h ${RESOURCE_FILES})

# Use files from main project
include_directories(../../app/src)

qt_add_qml_module(
  debug-qml
  URI
  qml.components
  VERSION
  1.0
  QML_FILES
  Main.qml
  # Use files from main project
  ../../app/qml/components/SliderCustom.qml
  ../../app/qml/components/Triangle.qml
  ../../app/qml/components/BackgroundDefault.qml
  ../../app/qml/components/ButtonClose.qml
  ../../app/qml/components/ButtonDefault.qml
  ../../app/qml/components/ButtonDraggable.qml
  ../../app/qml/components/ButtonIcon.qml
  ../../app/qml/components/ButtonIconColor.qml
  ../../app/qml/components/ComboBoxDefault.qml
  ../../app/qml/components/GroupBoxDefault.qml
  ../../app/qml/components/ImageDefault.qml
  ../../app/qml/components/MenuCheckBox.qml
  ../../app/qml/components/MenuDefault.qml
  ../../app/qml/components/RoundButtonDefault.qml
  ../../app/qml/dialogs/PathBox.qml
  ../../app/qml/dialogs/PopupDefault.qml
  ../../app/qml/dialogs/DialogSettings.qml)

target_link_libraries(
  debug-qml
  PRIVATE Qt6::Core Qt6::Quick)

install(
  TARGETS debug-qml
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
