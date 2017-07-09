CMAKE_MINIMUM_REQUIRED(VERSION 2.8) 

project(GenomeSequenceSimulator)

set(CMAKE_CXX_FLAGS  "-g -std=c++11 -DDEBUG")

include_directories(${PROJECT_SOURCE_DIR})

set(source_cpp main.cpp config.cpp)
set(source_h config.h)

include(utils/CMakeLists.txt)
include(thirdPart/CMakeLists.txt)
include(genomeSequence/CMakeLists.txt)

add_executable(GSS  ${source_h} ${source_cpp})

