cmake_minimum_required(VERSION 3.5)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(SyntheticSchmup)

set(SOURCE_DIR $ENV{SOURCE_DIR})
set(BUILD_DIR $ENV{BUILD_DIR})
set(EXTERNALS_DIR $ENV{EXTERNALS_DIR})

#message(STATUS "source_dir : ${SOURCE_DIR}")
#message(STATUS "${BUILD_DIR}")
#message(STATUS "${EXTERNALS_DIR}")

#return()

# If multi-configuration types
if(CMAKE_CONFIGURATION_TYPES)
    set(SyntheticSchmup_CONFIGURATION $ENV{SyntheticSchmup_CONFIGURATION})
    if(SyntheticSchmup_CONFIGURATION)
        set(CMAKE_CONFIGURATION_TYPES ${SyntheticSchmup_CONFIGURATION} CACHE STRING "" FORCE)
    else()
        message("The environment variable SyntheticSchmup_CONFIGURATION must be defined to Superbuild, RelWithDebInfo or Debug")
    endif()
else()
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose configuration")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Superbuild RelWithDebInfo Debug)

    # We want to only present the choice of configurations at the first CMake configuration
    if(NOT ADAM_CONFIG_CHOSEN)
        set(ADAM_CONFIG_CHOSEN ON CACHE STRING "" FORCE)
        mark_as_advanced(ADAM_CONFIG_CHOSEN)
        return()
    endif()
endif()

message("${SyntheticSchmup_CONFIGURATION}")

# Build dependencies or not
if("${SyntheticSchmup_CONFIGURATION}" STREQUAL "Superbuild" OR "${CMAKE_BUILD_TYPE}" STREQUAL "Superbuild")
    set(SUPERBUILD_USE ON)
else()
    set(SUPERBUILD_USE OFF)
endif()


if(SUPERBUILD_USE)
    message(STATUS "Superbuild build")
    include(ExternalProject)

    set(Deb_PREFIX "${EXTERNALS_DIR}/Debug")
    set(Rel_PREFIX "${EXTERNALS_DIR}/Release")
    
    #set(Debug_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/Debug")
    set(sfml_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/sfml")
    set(sfml_Deb "${Deb_PREFIX}/sfml")
    set(sfml_Rel "${Rel_PREFIX}/sfml")
    set(sfml_Deb_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${sfml_Deb} -DCMAKE_BUILD_TYPE=Debug)
    set(sfml_Rel_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${sfml_Rel} -DCMAKE_BUILD_TYPE=Release)
    # if(UNIX)
        # ExternalProject_Add(SFML_Debug
            # PREFIX ${sfml_PREFIX}
            # URL /home/jessy/Dropbox/GitHub/SyntheticSchmup/SFML-2.4.0-sources.zip
            # CMAKE_ARGS ${sfml_Deb_CMAKE_ARGS}
            # #INSTALL_DIR "/home/jessy/Dropbox/GitHub/SyntheticSchmup-build/Superbuild/sfml/Debug"
            # #INSTALL_COMMAND ""
        # )
        # ExternalProject_Add(SFML_Release
            # PREFIX ${sfml_PREFIX}
            # URL /home/jessy/Dropbox/GitHub/SyntheticSchmup/SFML-2.4.0-sources.zip
            # CMAKE_ARGS ${sfml_Rel_CMAKE_ARGS}
        # #    INSTALL_DIR "/home/jessy/Dropbox/GitHub/SyntheticSchmup-build/Superbuild/sfml/Release"
        # #    #INSTALL_COMMAND ""
        # )
    # elseif(WIN32)
        ExternalProject_Add(SFML_Debug
            PREFIX ${sfml_PREFIX}
            URL http://www.sfml-dev.org/files/SFML-2.4.0-sources.zip
            CMAKE_ARGS ${sfml_Deb_CMAKE_ARGS}
            BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Debug --target install
            INSTALL_COMMAND ""
        )
        ExternalProject_Add(SFML_Release
            PREFIX ${sfml_PREFIX}
            URL http://www.sfml-dev.org/files/SFML-2.4.0-sources.zip
            CMAKE_ARGS ${sfml_Rel_CMAKE_ARGS}
            BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Release --target install
            INSTALL_COMMAND ""
        )
    # endif()
else()
    message(STATUS "SynthetiSchmup build")
    if(WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")   # turn level of warning 4 and warning as error
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")   # turn level of warning 4 and warning as error
    endif()
    
    set(SFML_ROOT "G:/Dropbox/GitHub/SyntheticSchmup-build/sfml")

    project(SyntheticSchmup)
    add_executable(a a.cpp)
    set_target_properties (a PROPERTIES
            FOLDER Window
            )

    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
    find_package(SFML 2 REQUIRED system window graphics network audio)
    if(SFML_FOUND)
      message(STATUS found)
      include_directories(${SFML_INCLUDE_DIR})
      target_link_libraries(a ${SFML_LIBRARIES})
    endif()
endif()
