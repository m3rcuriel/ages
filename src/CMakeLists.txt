cmake_minimum_required(VERSION 2.8)


project(AGES)

set(COMPILE_FLAGS "-std=c++11")

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 001)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(gen)
include_directories(rivergen)

add_executable (demo main.cpp gen/simplex.cpp rivergen/rivergen.cpp rivergen/ocean_fill.cpp graphicsLoop.cpp)

target_link_libraries(demo sfml-graphics sfml-window sfml-system)
