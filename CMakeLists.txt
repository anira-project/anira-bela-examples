cmake_minimum_required(VERSION 3.15)

################################################################
# Define the options for the anira library
################################################################

option(ANIRA_BELA_INFERENCE_EXAMPLE "Build the example anira-bela-inference" ON)
option(ANIRA_BELA_BENCHMARK_EXAMPLE "Build the example anira-bela-benchmark" ON)

option(ANIRA_WITH_INSTALL "Bundle the anira library" ON) # This only works if anira is added as a submodule

################################################################
# Get project version from latest git tag
################################################################

execute_process(COMMAND git describe --dirty
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE PROJECT_VERSION_FULL
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND git describe --tags --abbrev=0
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE PROJECT_VERSION_SHORT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Retrive the v from the short version string
string(SUBSTRING ${PROJECT_VERSION_SHORT} 1 -1 PROJECT_VERSION_SHORT)
string(SUBSTRING ${PROJECT_VERSION_FULL} 1 -1 PROJECT_VERSION_FULL)

################################################################
# Setup the project
################################################################

set(PROJECT_NAME "anira-bela-examples")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION_SHORT})
message(STATUS "Building ${PROJECT_NAME} - Version: ${PROJECT_VERSION_SHORT} (${PROJECT_VERSION_FULL})")

if(ANIRA_BELA_BENCHMARK_EXAMPLE)
    set(ANIRA_WITH_BENCHMARK ON)
endif()

################################################################
# Setting up anira
################################################################

# There are two ways adding anira to your project:

# 1. Add as submodule and use add_subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/anira) # set this to the path of the anira library

# 2. Use the precompiled version of anira
# list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/anira-1.0.1-Linux-armv7l") # set this to the path of the precompiled anira library
# find_package(anira REQUIRED)

################################################################
# Define the path of the models on the Bela board
################################################################

add_compile_definitions(MODELS_PATH="/root/models")

################################################################
# Add examples
################################################################

if(ANIRA_BELA_INFERENCE_EXAMPLE)
    add_subdirectory(anira-bela-inference)
endif()
if(ANIRA_BELA_BENCHMARK_EXAMPLE)
    add_subdirectory(anira-bela-benchmark)
endif()

################################################################
# Set the install prefix
################################################################

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}-${PROJECT_VERSION_SHORT}" CACHE PATH "Where the library will be installed to" FORCE)
message(STATUS "CMAKE_INSTALL_PREFIX is set to ${CMAKE_INSTALL_PREFIX}")
