cmake_minimum_required(VERSION 3.15)

################################################################
# Setup the project
################################################################

set(PROJECT_NAME "anira-bela-inference")
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
# Adding the executable
################################################################

file(GLOB SRC_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

################################################################
# Define the path of the models
################################################################

target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    AUDIO_PATH="/root/audio"
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

################################################################
# Setup the install target
################################################################

include(cmake/install.cmake)
