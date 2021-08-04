cmake_minimum_required(VERSION 3.14)

project(tidy-images
    VERSION 1.0.0
    LANGUAGES CXX)

# Options
option( APP_BUILD_PLUGINS "Build plugins (be sure dependencies are installed and in PATH)" ON )
option( APP_BUILD_TESTS   "Build unit tests"                                               ON )
option( APP_BUILD_DOC     "Generate documentation (requires Doxygen)"                      ON )
option( APP_COPY_SAMPLES  "Copy samples to application folder"                             ON )

# Main application
add_subdirectory(app)

# Plugins
if( APP_BUILD_PLUGINS )
    add_subdirectory( plugins/exiv2  )
    add_subdirectory( plugins/opencv )
endif()

# Unit tests
if( APP_BUILD_TESTS )
    add_subdirectory( tests/test_app )
endif()

# Documentation
if( APP_BUILD_DOC )
    add_subdirectory( docs )
endif()

# Copy samples
if( APP_COPY_SAMPLES )
    file(GLOB samples "samples/*")
    file(COPY ${samples} DESTINATION "app/samples")
endif()
