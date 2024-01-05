cmake_minimum_required(VERSION 3.16)

project(
  tidy-images
  VERSION 0.83.0
  LANGUAGES CXX)

# Options
option(APP_BUILD_PLUGINS  "Build plugins (be sure dependencies are installed and in PATH)" ON )
option(APP_BUILD_TESTS    "Build unit tests"                                               ON )
option(APP_BUILD_DOC      "Generate documentation (requires Doxygen)"                      OFF)
option(APP_COPY_SAMPLES   "Copy samples to application folder"                             ON )
option(APP_STATIC_BUILD   "Build static application"                                       OFF)
option(APP_STATIC_PLUGINS "Build and add static plugins to the application"                OFF)

# Main application
add_subdirectory(app)
# Build app without console
set_target_properties(tidy-images PROPERTIES WIN32_EXECUTABLE TRUE)

# Plugins
if(APP_BUILD_PLUGINS)
  add_subdirectory(plugins/exiv2)
  add_subdirectory(plugins/opencv)
endif()

# Unit tests
if(APP_BUILD_TESTS)
  add_subdirectory(tests)
endif()

# Documentation
if(APP_BUILD_DOC)
  add_subdirectory(docs)
endif()

# Copy samples
if(APP_COPY_SAMPLES)
  file(GLOB samples "samples/*")
  file(COPY ${samples} DESTINATION "app/samples")
endif()
