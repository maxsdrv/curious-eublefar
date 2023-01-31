project(temp)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")

set(source)
set(headers)

list(APPEND source
        source/LinkedList.cpp
        source/MyArray.cpp
        source/BinarySearch.cpp)
list(APPEND headers
        include/LinkedList.h
        include/MyArray.h
        include/BinarySearch.h
        include/profile.h)
include_directories(include)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMKAE_BUILD_TYPE "Debug")
endif()

add_executable(${PROJECT_NAME} ${source} ${headers} main.cpp)

