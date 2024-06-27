cmake_minimum_required(VERSION 3.18)

project(http_server)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.c
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
