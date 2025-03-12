cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(SOURCES
    cliutils.c
    cpu.c
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(cliutils ${SOURCES})