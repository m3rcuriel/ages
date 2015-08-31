cmake_minimum_required(VERSION 2.8)


project(AGES)

set(COMPILE_FLAGS "-std=c++11 -g -O0")
file(GLOB_RECURSE SRC_FILES src/*.cpp)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build/")

add_executable (demo ${SRC_FILES})

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(demo ${SFML_LIBRARIES})
endif()
