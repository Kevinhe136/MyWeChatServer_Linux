cmake_minimum_required (VERSION 2.8)

project (Server)

add_compile_options(-std=c++11)

aux_source_directory(. DIR_SRCS)

include_directories("~/MyProgram/MyWeChatServer_Linux/headfiles")
include_directories("/usr/include/mysql")
#link_directories(~/MyProgram/MyWeChatServer_Linux/sourcefiles)
link_directories(/usr/lib/mysql/plugin)
link_directories(/usr/lib/x86_64-linux-gnu)
#link_libraries(libmysqlclient.a)
link_libraries(libmysqlclient.so)
link_libraries(libpthread.so)

add_executable(EpollServer ${DIR_SRCS})

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread")

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
