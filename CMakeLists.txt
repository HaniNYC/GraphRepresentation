
cmake_minimum_required(VERSION 2.8)
project(findPaths)
add_definitions(-g)

FIND_PACKAGE(Boost 1.50.0 REQUIRED)
INCLUDE_DIRECTORIES (
    ${Boost_INCLUDE_DIRS}
)


add_executable(findPaths main.cpp fileReader.cpp QuadraticProbing.cpp)
