CMAKE_MINIMUM_REQUIRED(VERSION 2.8) 

project(GenomeSequenceSimulator)

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

#set(CMAKE_CXX_FLAGS "-g -std=c++11 -DDEBUG")
set(CMAKE_CXX_FLAGS "-std=c++11 -O2") 

include_directories(${PROJECT_SOURCE_DIR})

set(source_cpp main.cpp config.cpp)
set(source_h config.h)

include(utils/CMakeLists.txt)
include(thirdPart/CMakeLists.txt)
include(genomeSequence/CMakeLists.txt)

add_executable(GSS  ${source_h} ${source_cpp})

