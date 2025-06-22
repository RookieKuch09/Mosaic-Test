cmake_minimum_required(VERSION 3.20)

project(MosaicTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Mosaic CONFIG REQUIRED)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable(mosaic-test ${SOURCES})

target_include_directories(mosaic-test PRIVATE "include")

target_link_libraries(mosaic-test PRIVATE Mosaic::Mosaic)
