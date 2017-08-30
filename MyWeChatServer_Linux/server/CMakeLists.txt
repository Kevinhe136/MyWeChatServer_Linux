cmake_minimum_required (VERSION 2.8)
project (Server)

aux_source_directory(. DIR_SRCS)

add_executable(EpollServer ${DIR_SRCS})

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
