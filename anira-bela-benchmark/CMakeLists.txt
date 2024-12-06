cmake_minimum_required(VERSION 3.15)

################################################################
# Setup the project
################################################################

set(PROJECT_NAME "anira-bela-benchmark")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION_SHORT})
message(STATUS "Building ${PROJECT_NAME} - Version: ${PROJECT_VERSION_SHORT} (${PROJECT_VERSION_FULL})")

# Sets the cpp language minimum
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

################################################################
# Adding the executable
################################################################

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    defineBelaBenchmark.cpp
	main.cpp
)

################################################################
# Linking the required libraries
################################################################

target_link_libraries(
    ${PROJECT_NAME}
    anira::anira
    dl
    rt
)

################################################################
# Setup the install target
################################################################

include(cmake/install.cmake)
