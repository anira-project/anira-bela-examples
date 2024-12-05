cmake_minimum_required(VERSION 3.15)

# ==============================================================================
# Define the options for the anira library
# ==============================================================================

# Shall the library be built as a shared library?
option(ANIRA_X_BELA_WITH_INSTALL "Add install targets" ON)
option(ANIRA_X_BELA_INFERENCE_EXAMPLE "Build the example anira-x-bela-inference" ON)
option(ANIRA_X_BELA_BENCHMARK_EXAMPLE "Build the example anira-x-bela-benchmark" OFF)

# ==============================================================================
# Get project version from latest git tag
# ==============================================================================

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

# ==============================================================================
# Setup the project
# ==============================================================================

set(PROJECT_NAME "anira-bela-examples")

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION_SHORT})

message(STATUS "Building ${PROJECT_NAME} - Version: ${PROJECT_VERSION_SHORT} (${PROJECT_VERSION_FULL})")

# ==============================================================================
# Add examples
# ==============================================================================

add_subdirectory(anira-x-bela-inference)
add_subdirectory(anira-x-bela-benchmark)

# ==============================================================================
# Add install targets
# ==============================================================================

if(ANIRA_WITH_INSTALL)
    include(cmake/install.cmake)
endif()
