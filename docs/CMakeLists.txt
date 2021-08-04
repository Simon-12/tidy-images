cmake_minimum_required(VERSION 3.14)

project(doc_app)

if( APP_BUILD_DOC )
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/config-file.doxygen)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/config-file.doxygen)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)

        # request to configure the file
        set(MY_INPUT INPUT="${CMAKE_CURRENT_SOURCE_DIR}/../app") # Set INPUT path
        set(MY_OUTPUT OUTPUT_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}") # Set OUTPUT path
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM )

    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the documentation")
    endif (DOXYGEN_FOUND)
endif()
