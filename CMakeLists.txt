cmake_minimum_required(VERSION 3.0)
project(server)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC
    server/log.cc
    server/util.cc
    tests/test.cc    
    )

add_library(server SHARED ${LIB_SRC})

add_executable(test1 ${LIB_SRC})
#add_dependencies(test server)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

