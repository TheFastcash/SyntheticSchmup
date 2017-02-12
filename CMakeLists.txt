cmake_minimum_required(VERSION 3.5)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(SyntheticSchmup)

set(SOURCE_DIR $ENV{SOURCE_DIR})
set(BUILD_DIR $ENV{BUILD_DIR})
set(EXTERNALS_DIR $ENV{EXTERNALS_DIR})
set(SFML_ROOT $ENV{SFML_ROOT})

message(STATUS "SOURCE_DIR    : ${SOURCE_DIR}")
message(STATUS "BUILD_DIR     : ${BUILD_DIR}")
message(STATUS "EXTERNALS_DIR : ${EXTERNALS_DIR}")
message(STATUS "SFML_ROOT     : ${SFML_ROOT}")


# return()

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
    #if(NOT SyntheticSchmup_CONFIG_CHOSEN)
    #    set(SyntheticSchmup_CONFIG_CHOSEN ON CACHE STRING "" FORCE)
    #    mark_as_advanced(SyntheticSchmup_CONFIG_CHOSEN)
    #    return()
    #endif()
endif()

message(STATUS "Configuration type : ${SyntheticSchmup_CONFIGURATION}")

# Build dependencies or not
if("${SyntheticSchmup_CONFIGURATION}" STREQUAL "Superbuild" OR "${CMAKE_BUILD_TYPE}" STREQUAL "Superbuild")
    set(SUPERBUILD_USE ON)
else()
    set(SUPERBUILD_USE OFF)
endif()


if(SUPERBUILD_USE)
    message(STATUS "Superbuild build")
    include(ExternalProject)

    set(sfml_PREFIX "${EXTERNALS_DIR}/sfml")
    set(sfml_Deb "${sfml_PREFIX}/Debug")
    set(sfml_Rel "${sfml_PREFIX}/Release")
    set(sfml_Deb_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${sfml_Deb}
                            -DCMAKE_BUILD_TYPE=Debug
                            -DSFML_BUILD_EXAMPLES:BOOL=ON
                            -DBUILD_SHARED_LIBS:BOOL=ON
                            )
    set(sfml_Rel_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${sfml_Rel}
                            -DCMAKE_BUILD_TYPE=Release
                            -DSFML_BUILD_EXAMPLES:BOOL=ON
                            -DBUILD_SHARED_LIBS:BOOL=ON
                            )
    ExternalProject_Add(SFML_Debug
        # PREFIX ${sfml_PREFIX}
        URL https://www.dropbox.com/s/z6to2so4t15mqtf/SFML-2.4.0-sources-fixed.zip
        CMAKE_ARGS ${sfml_Deb_CMAKE_ARGS}
        BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Debug --target install
        # BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Debug
        INSTALL_COMMAND ""
    )
    ExternalProject_Add(SFML_Release
        # PREFIX ${sfml_PREFIX}
        URL https://www.dropbox.com/s/z6to2so4t15mqtf/SFML-2.4.0-sources-fixed.zip
        CMAKE_ARGS ${sfml_Rel_CMAKE_ARGS}
        BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Release --target install
        # BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Release
        INSTALL_COMMAND ""
    )
else()
    project(SyntheticSchmup)
    message(STATUS "SynthetiSchmup build")
    if(WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")   # turn level of warning 4 and warning as error
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")   # turn level of warning 4 and warning as error
    endif()
    
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
    find_package(SFML 2 REQUIRED system window graphics network audio)
    find_package(OpenGL)
    
    set(all_found ON)
    if(SFML_FOUND)
        message(STATUS ${SFML_LIBRARIES})
        include_directories(${SFML_INCLUDE_DIR})
    else()
        message(WARNING "SFML not found !")
        set(all_found OFF)
    endif()
    if(OPENGL_FOUND AND OPENGL_GLU_FOUND)
        message(STATUS ${OPENGL_LIBRARIES})
        include_directories(${OPENGL_INCLUDE_DIR})
    else()
        message(WARNING "OpenGL not found !")
        set(all_found OFF)
    endif()
    
    if(all_found)
        add_subdirectory(Programme)
    endif()
endif()
