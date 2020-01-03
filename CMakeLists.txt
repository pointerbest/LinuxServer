cmake_minimum_required(VERSION 3.0)
project(server)


set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(~/mryang/yaml-cpp/include)
link_directories(~/mryang/LinuxServer/lib)

#find_library(YAMLCPP libyaml-cpp.a)
find_library(YAMLCPP yaml-cpp)
message("***", ${YAMLCPP})

set(LIB_SRC
    server/log.cc
    server/util.cc
    server/config.cc
    )

add_library(server SHARED ${LIB_SRC})

add_executable(test1 tests/test.cc)
add_dependencies(test1 server)
target_link_libraries(test1 server ${YAMLCPP})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config server)
target_link_libraries(test_config server ${YAMLCPP})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

