cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "anira-x-bela-inference")

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION_SHORT})

message(STATUS "Building ${PROJECT_NAME} - Version: ${PROJECT_VERSION_SHORT} (${PROJECT_VERSION_FULL})")

# Sets the cpp language minimum
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

################################################################
# Setup required by Bela
################################################################

add_compile_options(
    -march=armv7-a
    -mtune=cortex-a8
    -mfloat-abi=hard
    -mfpu=neon
    -Wno-psabi
)

add_compile_options(
    -O3
    -g 
    -fPIC
    -ftree-vectorize
    -ffast-math
)

add_compile_definitions(DXENOMAI_SKIN_posix)

################################################################

find_library(COBALT_LIB REQUIRED
    NAMES cobalt libcobalt
    HINTS "${CMAKE_SYSROOT}/usr/xenomai/lib"
)

find_library(NEON_LIB REQUIRED
    NAMES NE10 libNE10
    HINTS "${CMAKE_SYSROOT}/usr/lib"
)

find_library(MATHNEON_LIB REQUIRED
    NAMES mathneon libmathneon
    HINTS "${CMAKE_SYSROOT}/usr/lib"
)

################################################################
# Setting up anira
################################################################

# The ANIRA_WITH_INSTALL option bundles the anira library with the executable
# This only works if anira is added as a submodule (see below)
if(ANIRA_X_BELA_WITH_INSTALL)
    set(ANIRA_WITH_INSTALL ON)
endif()

# There are two ways adding anira to your project:

# 1. Add as submodule and use add_subdirectory
add_subdirectory(anira) # set this to the path of the anira library

# 2. Use the precompiled version of anira
# list(APPEND CMAKE_PREFIX_PATH "anira-0.1.0-bela") # set this to the path of the precompiled anira library
# find_package(anira REQUIRED)

################################################################
# Adding the executable
################################################################

file(GLOB SRC_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

################################################################
# Define the path of the models
################################################################

if(NOT DEFINED ANIRA_X_BELA_MODELS_PATH)
    set(ANIRA_X_BELA_MODELS_PATH "/root/models")
endif()

target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    MODELS_PATH="/root/models"
)

################################################################
# Adding include directories from cross-compilation toolchain
################################################################

target_include_directories(
    ${PROJECT_NAME} PRIVATE ${BELA_ROOT} ${BELA_ROOT}/include 
)

################################################################
# Linking the required libraries
################################################################

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${BELA_ROOT}/lib/libbelafull.so
    anira::anira
    ${COBALT_LIB}
    ${NEON_LIB}
    ${MATHNEON_LIB}
    dl
    prussdrv
    asound
    atomic
    sndfile
    pthread
    rt
)
